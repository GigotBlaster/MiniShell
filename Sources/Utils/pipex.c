/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:54:20 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 18:10:17 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *acces_command(char *cmd_name, char **paths)
{
	int i;
	char *cmd_path;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_pipexstrjoin(paths[i], cmd_name);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK | F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char *find_path(char *cmd_name, char **env)
{
	int i;
	char **paths;
	char *cmd_path;

	i = 0;
	while (env[i] && ft_pipexstrncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (write(STDERR_FILENO, "env not found \n", 15), NULL);
	paths = ft_pipexsplit(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = paths[i];
		paths[i] = ft_pipexstrjoin(paths[i], "/");
		free(cmd_path);
		i++;
	}
	cmd_path = acces_command(cmd_name, paths);
	ft_pipexfrees(paths);
	return (cmd_path);
}

void init(t_pipex *pipex, char **env, int ac, char **av)
{
	pipex->env = env;
	pipex->prev = -1;
	pipex->cmds = av;

	pipex->pid = malloc(sizeof(int) * pipex->nbcmd);
}

void redirection(t_pipex *pipex, int i)
{
	if (i != 0)
	{
		dup2(pipex->prev, STDIN_FILENO);
		close(pipex->prev);
	}
	if (i != pipex->nbcmd -1)
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);

	/////////////////////////////////////////////////////////////////////// redirection fichiers
}

void child_process(t_pipex *pipex, char *arg, int i)
{
	free(pipex->pid);
	redirection(pipex, i);
	fprintf(stderr, "arg--->>%s\n", arg);
	char **tab = ft_pipexsplit(arg, ' '); // a la place t'appelles create_cmd
	for (int i = 0; tab[i]; i++)
		fprintf(stderr, "--->%s\n", tab[i]);
	char *cmd = find_path(tab[0], pipex->env);
	if (cmd)
		execve(cmd, tab, pipex->env);
	// free tout caue tu peux
	printf("%s: command not found\n", tab[0]); 
	exit(127);
}

void parent_process(t_pipex *pipex)
{
	if (pipex->prev != -1)
		close(pipex->prev);
	pipex->prev = pipex->pipe_fd[0];
	close(pipex->pipe_fd[1]);
}

void process(t_pipex *pipex)
{
	int i = 0;
	while (i < pipex->nbcmd)
	{
		pipe(pipex->pipe_fd);
		pipex->pid[i] = fork();
		if (pipex->pid[i] == 0) // child process
			child_process(pipex, pipex->cmds[i], i);
		else
			parent_process(pipex);
		i++;
	}
}

// ./pipex ls cat grep lsblk echo
int ft_pipe(t_pipex *pipex, char **av, char **env) //char **av res split tableau
{
	init(pipex, env, pipex->nbcmd, av);
	process(pipex);
	for (int i = 0; i < pipex->nbcmd; i++)
		waitpid(pipex->pid[i], NULL, 0);
	close(pipex->pipe_fd[0]);
	// free pid
	return (0);
}


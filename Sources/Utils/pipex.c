/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:54:20 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 16:39:32 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*acces_command(char *cmd_name, char **paths)
{
	int		i;
	char	*cmd_path;

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

char	*find_path(char *cmd_name, char **env)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	if (ft_strchr(cmd_name, '/') != NULL)
		return (cmd_name);
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

void	init(t_pipex *pipex, char **env, char **av, bool first_time)
{
	int	i;
	i = 0;
	if (first_time)
		pipex->env = env;
	pipex->prev = -1;
	pipex->cmds = av;
	pipex->pid = malloc(sizeof(int) * pipex->nbcmd);
	while (i < pipex->nbcmd)
	{
		pipex->pid[i] = 0;
		i++;
	}
}

int	get_pipe(t_pipex *here, t_info *data)
{
	(void)data;
	if (here->prev > -1)
		dupclose(here->prev, STDIN_FILENO);
	if (here->pipe_fd[1] > -1)
		dupclose(here->pipe_fd[1], STDOUT_FILENO);
	if (here->pipe_fd[0] > -1)
		close(here->pipe_fd[0]);
	return (-1);
}



int	ft_pipe(t_pipex *pipex, char **av, char **env, bool first_time)
{
	init(pipex, env, av, first_time);
	process(pipex);
	free(pipex->pid);
	return (0);
}

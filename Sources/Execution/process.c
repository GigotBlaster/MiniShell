/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:51:14 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 18:28:28 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_pipex *pipex, char *arg, int i)
{
	t_cmd	*all;
	char	*cmd;


	all = token(arg);
	if (all->redirection[0])
		;
	else if (!all || !all->arguments || !all->arguments[0])
	{
		free_all(pipex, all);
		exit(0);
	}
	file(NULL, all, i);
	if (check_built_in_baby(pipex, arg))
	{
		printf("built in success\n"); //oust
		free_all(pipex, all);
		exit(0);
	}
	all->environnement = pipex->env;
	cmd = find_path(all->command, pipex->env);
	if (cmd)
	{
		close(pipex->pipe_fd[0]);
		if (i > 0)
			close(pipex->prev);
		if (i < pipex->nbcmd - 1)
			close(pipex->pipe_fd[1]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(cmd, all->arguments, pipex->env);
	}
	printf("%s: command not found\n", all->command);
	free_all(pipex, all);
	exit(127);
}

void	parent_process(t_pipex *pipex)
{
	if (pipex->prev != -1)
		close(pipex->prev);
	close(pipex->pipe_fd[1]);
	pipex->prev = pipex->pipe_fd[0];
}

void	error_signal(int *cnt)
{
	if (g_return_value == 128 + SIGTERM)
		printf("Terminated\n");
	else if (g_return_value == 128 + SIGSEGV)
		printf("Segmentation fault (core dumped)\n");
	else if (g_return_value == 128 + SIGQUIT && !(*cnt))
	{
		printf("\nQuit (core dumped)\n");
		(*cnt)++;
	}
	else if (g_return_value == 128 + SIGABRT)
		printf("Aborted (core dumped)\n");
}

void	process(t_pipex *pipex)
{
	int		i;
	int		fd_in;
	pid_t	pid;

	i = 0;
	fd_in = STDIN_FILENO;
	while (i < pipex->nbcmd)
	{
		pipe(pipex->pipe_fd);
		if (check_built_in_dad(pipex, pipex->cmds[i]) != 1)
		{
			g_return_value = 0;
			pid = fork();
			if (pid == 0)
			{
				close(pipex->pipe_fd[0]);
				if (i > 0)
				{
					dupclose(fd_in, STDIN_FILENO);
					close(fd_in);
				}
				if (i < pipex->nbcmd - 1)
				{
					dupclose(pipex->pipe_fd[1], STDOUT_FILENO);
					close(pipex->pipe_fd[1]);
				}
				child_process(pipex, pipex->cmds[i], i);
			}
			else
			{
				pipex->pid[i]=pid;
				parent_process(pipex);
				close(pipex->pipe_fd[1]);
				fd_in = pipex->pipe_fd[0];
			}
		}else{
			pipex->pid[i]=0;
		}
		i++;
	}
	i = -1;
	int cnt=0;
	int status;
	while (++i < pipex->nbcmd)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (pipex->pid[i] > 0)
		{
			if (WIFEXITED(status))
				g_return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_return_value = 128 + WTERMSIG(status);
				error_signal(&cnt);
			}
			printf("3------------->%d\n", g_return_value);
		}
	}
	close(pipex->pipe_fd[0]);
}

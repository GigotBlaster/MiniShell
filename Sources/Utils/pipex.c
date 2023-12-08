/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:54:20 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 13:37:18 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_return_value;

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
	{
		return (cmd_name);
	}
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

void	init(t_pipex *pipex, char **env, char **av)
{
	pipex->env = env;
	pipex->prev = -1;
	pipex->cmds = av;
	pipex->pid = malloc(sizeof(int) * pipex->nbcmd);
}

/////////////////////////////////////////////////////////////////////// redirection fichiers

void	dupclose(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

void	ft_freeredir(t_cmd *cmd)
{
	int i = 0;
	while (cmd->fichiers[i])
		ft_free(cmd->fichiers[i++]);
	ft_free(cmd->redirection);
}

void	ft_errorcmd(t_info *data, t_cmd *cmd, char *str)
{
	(void) data;
	(void) str;
	ft_free((void **)&cmd->flag);
	ft_free((void **)&cmd->command);
	ft_freeredir(cmd);
}

void	error_fd(t_info *data, t_cmd *cmd, int i)
{
	if (errno == 13 && cmd->redirection[i] != 4)
		fprintf(stderr, "bash: %s: Permission denied\n", cmd->fichiers[i]);
	else if (cmd->redirection[i] != 4)
		fprintf(stderr, "bash: %s: No such file or directory\n",
			cmd->fichiers[i]);
	ft_errorcmd(data, cmd, "");
	close(data->fd[1]);
	close(data->fd[0]);
	exit(1);
}

int	get_pipe(t_pipex *here, t_info *data)
{
	(void)data;
	int	i;

	i = -1;
	if (here->prev > -1)
		dupclose(here->prev, STDIN_FILENO);
	if (here->pipe_fd[1] > -1)
		dupclose(here->pipe_fd[1], STDOUT_FILENO);
	if (here->pipe_fd[0] > -1)
		close(here->pipe_fd[0]);
	return (-1);
}

int     ft_heredoc(int fd, char *charset)
{
    char *prompt;
    prompt = readline(">");
    while (prompt && ft_strcmp(prompt, charset) != 0)
    {
        write(fd, prompt, ft_strlen(prompt));
        write(fd, "\n", 1);
		prompt = readline(">");
	}
    return (1);
}

void	file(t_info *data, t_cmd *cmd, int a) //with suz
{
	int	fd;
	int	i;
	int fd_in;
	int fd_out; 

	i = 0;
	fd_in = -1;
	fd_out = -1;
	while (cmd->redirection[i])
	{
		printf("here\n");
		if (cmd->redirection[i] == 1)
			fd = open(cmd->fichiers[i], O_TRUNC | O_WRONLY | O_CREAT, 0666);
		else if (cmd->redirection[i] == 2)
			fd = open(cmd->fichiers[i], O_APPEND | O_WRONLY | O_CREAT, 0666);
		else if (cmd->redirection[i] == 3)
			fd = open(cmd->fichiers[i], O_RDONLY);
		else if (cmd->redirection[i] == 4)
        {
            fd = open(".tmp_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
            if (fd < 0)
                perror("ERROR CAN't open FD:");
            ft_heredoc(fd, cmd->fichiers[i]);
			

			// permet d avoir les bonne permission pour la lecture du fichier
			close(fd);
			fd = open(".tmp_heredoc", O_RDONLY);
        }
		else if (cmd->redirection[i] == 5)
			get_pipe(data->here, data);

		if (fd == -1)
			error_fd(data, cmd, a);
		else if (cmd->redirection[i] > 2 && cmd->redirection[i]  < 5)
			fd_in = fd;
		else if (cmd->redirection[i] < 3)
			fd_out = fd;
		fd = -1;
		i++;
	}
	
	//le faire hors du while pour que les heredoc aient toujours acces au stdin
	
	if (fd_in > -1)
		dupclose(fd_in, STDIN_FILENO);
	else if (fd_out > -1)
		dupclose(fd_out, STDOUT_FILENO);
	free(cmd->redirection);
}

int	check_built_in_exp(t_pipex *p, char *str) //suz
{
	t_cmd	*cmd;
	cmd = token(str);
	if (ft_strncmp(cmd->arguments[0], "pwd", 4) == 0)
	{
		ft_pwd(cmd);
		return (1);
	}
	if (ft_strncmp(cmd->arguments[0], "env", 4) == 0)
	{
		ft_env(p, cmd);
		return (1);
	}
	if (ft_strncmp(cmd->arguments[0], "echo", 5) == 0)
    {
        ft_echo(cmd);
        return (1);
    }
	if (ft_strncmp(cmd->arguments[0], "cd", 3) == 0)
    {
        ft_cd(p, cmd, 0);
        return (1);
    }
	return (0);
}

void child_process(t_pipex *pipex, char *arg, int i)
{
    t_cmd   *all;
    char    *cmd;

    all = token(arg);   // create_cmd
    file(NULL, all, i);
    if (check_built_in_exp(pipex, arg))
    {
        printf("built in success\n");
        exit(0);
    }
    free(pipex->pid);
    all->environnement = pipex->env;
    cmd = find_path(all->command, pipex->env);
    if (cmd)
    {
        close(pipex->pipe_fd[0]); // fermer le descripteur de lecture du pipe
        if (i > 0)
        {
            close(pipex->prev); // fermer le descripteur d'entrée standard
        }
        if (i < pipex->nbcmd - 1)
        {
            close(pipex->pipe_fd[1]); // fermer le descripteur d'écriture du pipe
        }
        execve(cmd, all->arguments, pipex->env);
        perror("execve"); // En cas d'échec de l'exécution de la commande
        exit(1);  // Ajout : sortie explicite du processus fils
    }
    printf("%s: command not found\n", all->command);
    exit(127);  // Ajout : sortie explicite du processus fils
}


void process(t_pipex *pipex)
{
    int i;
    int fd_in = STDIN_FILENO;

    for (i = 0; i < pipex->nbcmd; i++)
    {
        pipe(pipex->pipe_fd);
        pipex->pid[i] = fork();

        if (pipex->pid[i] == 0)
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
            close(pipex->pipe_fd[1]);
            fd_in = pipex->pipe_fd[0];
        }
    }

    // Fermer le descripteur de fichier de lecture du pipe dans le processus parent
    close(pipex->pipe_fd[0]);

    for (i = 0; i < pipex->nbcmd; i++)
    {
        waitpid(pipex->pid[i], NULL, 0);
    }

    // Fermer les descripteurs de fichiers associés aux processus fils
    for (i = 0; i < pipex->nbcmd; i++)
    {
        close(pipex->pid[i]);
    }
}




// void	process(t_pipex *pipex)
// {
// 	int	i;

// 	i = 0;
// 	int	fd_in = STDIN_FILENO;
// 	while (i < pipex->nbcmd)
// 	{
// 		pipe(pipex->pipe_fd);
// 		pipex->pid[i] = fork();
// 		if (pipex->pid[i] == 0)
// 		{
// 			close(pipex->pipe_fd[0]);
// 			if (i > 0)
// 			{
// 				dupclose(fd_in, STDIN_FILENO);
// 				close(fd_in);
// 			}
// 			if (i < pipex->nbcmd - 1)
// 			{
// 				dupclose(pipex->pipe_fd[1], STDOUT_FILENO);
// 				close(pipex->pipe_fd[1]);
// 			}
// 			child_process(pipex, pipex->cmds[i], i);
// 		}
// 		else
// 		{
// 			close(pipex->pipe_fd[1]); 
// 			fd_in = pipex->pipe_fd[0];
// 		}
// 		i++;
// 	}
// 	for (int i = 0; i < pipex->nbcmd; i++)
// 		waitpid(pipex->pid[i], NULL, 0);
// 	close(pipex->pipe_fd[0]);
// }

int	ft_pipe(t_pipex *pipex, char **av, char **env) // remake av ??
{
	init(pipex, env, av);  // ??init(pipex, env, pipex->nbcmd, av);
	process(pipex);
	return (0);
}

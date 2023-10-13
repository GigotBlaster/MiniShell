#include "pipex.h"

void	ft_frees(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	ft_error(void)
{
	perror("pipex");
	exit(1);
}

void	fail_execve(char **arg)
{
	write(STDERR_FILENO, "pipex: ", 7);
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, arg[0], ft_strlen(arg[0]));
	write(STDERR_FILENO, "\n", 1);
	exit(127);
}

void	first_cmd(char **env, char *infile, char **arg, int *pipe_fd)
{
	int		fd;
	char	*cmd_path;

	cmd_path = NULL;
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		return (close_all(fd, pipe_fd), ft_frees(arg), ft_error());
	if (!ft_strchr(arg[0], '/'))
		cmd_path = find_path(arg[0], env);
	else
	{
		if (access(arg[0], X_OK | F_OK) == 0)
			cmd_path = arg[0];
		else
			write(STDERR_FILENO, "No such file or directory\n", 26);
	}
	if (!cmd_path)
		return (ft_frees(arg), close_all(fd, pipe_fd), exit(1));
	if (dup2(pipe_fd[1], 1) == -1 || dup2(fd, 0) == -1)
		return (close_all(fd, pipe_fd), ft_error());
	close_all(fd, pipe_fd);
	if (execve(cmd_path, arg, env) == -1)
		fail_execve(arg);
}

void	second_cmd(char **env, char *outfile, char **arg, int *pipe_fd)
{
	int		fd;
	char	*cmd_path;

	cmd_path = NULL;
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (close_all(fd, pipe_fd), ft_frees(arg), ft_error());
	if (!ft_strchr(arg[0], '/'))
		cmd_path = find_path(arg[0], env);
	else
	{
		if (!access(arg[0], X_OK | F_OK))
			cmd_path = arg[0];
		else
			write(STDERR_FILENO, "No such file or directory\n", 26);
	}
	if (!cmd_path)
		return (ft_frees(arg), close_all(fd, pipe_fd), exit(1));
	if (dup2(pipe_fd[0], 0) == -1 || dup2(fd, 1) == -1)
		return (close_all(fd, pipe_fd), ft_error());
	close_all(fd, pipe_fd);
	if (execve(cmd_path, arg, env) == -1)
		fail_execve(arg);
}

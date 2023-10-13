#include "pipex.h"

char	*acces_command(char *cmd_name, char **paths)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_name);
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
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (write(STDERR_FILENO, "env not found \n", 15), NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(cmd_path);
		i++;
	}
	cmd_path = acces_command(cmd_name, paths);
	ft_frees(paths);
	if (!cmd_path)
		write(STDERR_FILENO, "command not found\n", 18);
	return (cmd_path);
}

int	initiate_child_process(char **av, int i, int *pipe_fd, char **env)
{
	pid_t	pidchild;
	char	**arg;

	pidchild = fork();
	if (pidchild == -1)
		ft_error();
	if (pidchild == 0)
	{
		arg = ft_split(av[i], ' ');
		if (arg == NULL)
			ft_error();
		if (i == 2)
			first_cmd(env, av[1], arg, pipe_fd);
		else if (i == 3)
			second_cmd(env, av[4], arg, pipe_fd);
		ft_frees(arg);
		exit(0);
	}
	return (pidchild);
}

int	main(int ac, char **av, char **env)
{
	int	pipe_fd[2];
	int	pid[2];

	if (ac != 5)
	{
		write(STDERR_FILENO, "Error : Wrong number of arguments\n", 34);
		exit(1);
	}
	if (!av[2][0] || !av[3][0])
		return (write(STDERR_FILENO, "pipex: No command\n", 18), 2);
	if (pipe(pipe_fd) == -1)
		ft_error();
	pid[0] = initiate_child_process(av, 2, pipe_fd, env);
	pid[1] = initiate_child_process(av, 3, pipe_fd, env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

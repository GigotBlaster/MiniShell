/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:30:06 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 11:08:56 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//PWD : Print Working Directory
//
#include "minishell.h"

void	change_stdin_stdout(t_info *cmd)
{
	if (cmd->output != STDOUT)
	{
		close(STDOUT);
		dup(cmd->output);
	}
	if (cmd->input != STDIN)
	{
		close(STDIN);
		dup(cmd->input);
	}
}

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;
	int		fd;

	(void)cmd;
	fd = 1;
	cwd = getcwd(NULL, 0); // Récupère le rép actuel
	printf("MON PWD :)\n");
	if (cwd == NULL)
	{
		perror("pwd");
		return (12);
	}
	if (write(fd, cwd, ft_strlen(cwd)) == -1)
	{
		write(2, "pwd: write error: No space left on device\n", 43);
		free(cwd);
		return (1);
	}
	write(fd, "\n", 1);
	free(cwd);
	return (SUCCESS);
}

void	update_pwd_vars(t_pipex *pipex, char *dir)
{
	char	*var;

	if (dir == NULL)
		return ;
	var = get_value_from_key("OLDPWD", pipex->env);
	if (var == NULL)
		cd_add_env_var(pipex, "OLDPWD", dir);
	else
	{
		cd_replace_env_var(pipex, "OLDPWD", dir);
		free(var);
	}
	dir = NULL;
	dir = getcwd(dir, 0);
	if (dir == NULL)
		return ;
	var = get_value_from_key("PWD", pipex->env);
	if (var == NULL)
		cd_add_env_var(pipex, "PWD", dir);
	else
	{
		cd_replace_env_var(pipex, "PWD", dir);
		free(var);
	}
}
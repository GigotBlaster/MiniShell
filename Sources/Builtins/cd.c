/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:20 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 17:38:43 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	change_directory(t_pipex *pipex, char *dest, int forg, char *current)
{
	struct stat	buf; // wtf
	if (stat(dest, &buf) < 0 && errno == EACCES)
		cd_error(pipex, dest, forg, 3);
	else if (access(dest, F_OK) != 0)
		cd_error(pipex, dest, forg, 1);
	else if (S_ISDIR(buf.st_mode))
	{
		current = getcwd(current, 0);
		if (chdir(dest) == -1)
		{
			if (current != NULL)
			{
				free(current);
				cd_error(pipex, dest, forg, 3);
				return ;
			}
		}
		if (forg == 1)
			exit(0); // free
		update_pwd_vars(pipex, current);
		printf("dans cd = %d\n", g_return_value);
		g_return_value = 0;
		return ;
	}
	else
		cd_error(pipex, dest, forg, 2);
}

void	go_to_home_dir(t_pipex *pipex, int forked, char *current_dir)
{
	char	*home;

	home = get_value_from_key("HOME", pipex->env);
	if (home == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		if (forked == 1)
			exit (1);
		g_return_value = 1;
		return ;
	}
	change_directory(pipex, home, forked, current_dir);
	free(home);
}

void	ft_cd(t_pipex *pipex, t_cmd *cmd, int forked)
{
	int		arg_nb;
	char	*current_dir;

	current_dir = NULL;
	arg_nb = count_line(cmd->arguments);
	printf("------------------>%i\n", arg_nb);
	if (arg_nb > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		// if (forked == 1)
		// 	exit(1);
		g_return_value = 1;
		return ;
	}
	else if (arg_nb == 1)
		go_to_home_dir(pipex, forked, current_dir);
	else
		change_directory(pipex, cmd->arguments[1], forked, current_dir);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:20 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 17:15:32 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error_handler(t_pipex *pipex, char *dest, int forg, char *current)
{
	if (current != NULL)
		free(current);
	cd_error(pipex, dest, forg, 3);
}

void	change_directory_success(t_pipex *pipex, char *dest, \
int forg, char *current)
{
	current = getcwd(current, 0);
	if (chdir(dest) == -1)
	{
		if (current != NULL)
			cd_error_handler(pipex, dest, forg, current);
	}
	if (forg == 1)
		exit(0);
	update_pwd_vars(pipex, current);
	g_return_value = 0;
}

void	change_directory(t_pipex *pipex, char *dest, int forg, char *current)
{
	struct stat	buf;

	if (stat(dest, &buf) < 0 && errno == EACCES)
		cd_error_handler(pipex, dest, forg, current);
	else if (access(dest, F_OK) != 0)
		cd_error_handler(pipex, dest, forg, current);
	else if (S_ISDIR(buf.st_mode))
		change_directory_success(pipex, dest, forg, current);
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
		if (forked == 1)
			exit(1);
		g_return_value = 1;
		return ;
	}
	else if (arg_nb == 1)
		go_to_home_dir(pipex, forked, current_dir);
	else
		change_directory(pipex, cmd->arguments[1], forked, current_dir);
}

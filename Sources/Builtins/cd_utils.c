/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:13:12 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 11:13:54 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_new_var(char *new, char *name, char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (name[i] != '\0')
	{
		new[i] = name[i];
		i++;
	}
	new[i] = '=';
	i++;
	while (value[j] != '\0')
	{
		new[i] = value[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(value);
}

void	cd_replace_env_var(t_pipex *pipex, char *name, char *value)
{
	int		i;
	char	*new;

	i = 0;
	while (pipex->env[i] != NULL
		&& !(ft_strncmp(pipex->env[i], name, ft_strlen(name)) == 0
			&& pipex->env[i][ft_strlen(name)] == '='))
		i++;
	new = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	if (new == NULL)
	{
		free(value);
		// ft_error(pipex, 1);
		exit(-1); // free!
	}
	free(pipex->env[i]);
	copy_new_var(new, name, value);
	pipex->env[i] = new;
}

void	replace_env(t_pipex *pipex, char **newenv, char *new)
{
	int	i;

	i = 0;
	while (pipex->env[i] != NULL)
	{
		newenv[i] = ft_strdup(pipex->env[i]);
		if (newenv[i] == NULL)
		{
			// free(new);
			// free_lex(newenv);
			// ft_error(sh, 1);
			exit(-1); //free
		}
		i++;
	}
	newenv[i] = new;
	newenv[i + 1] = NULL;
	free_lex(pipex->env);
	pipex->env = newenv;
}

void	cd_add_env_var(t_pipex *pipex, char *name, char *value)
{
	char	*new;
	char	**newenv;
	int		i;

	new = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	if (new == NULL)
	{
		free(value);
		exit(-1); //free
	}
	copy_new_var(new, name, value);
	i = 0;
	while (pipex->env[i] != NULL)
		i++;
	newenv = malloc(sizeof(char *) * (i + 2));
	if (newenv == NULL)
		exit(-1); //free
	replace_env(pipex, newenv, new);
}

void	cd_error(t_pipex *pipex, char *dest, int forked, int type)
{
	(void)pipex;
	if (type == 1)
	{
		ft_putstr_fd("msh: cd : ", 2);
		ft_putstr_fd(dest, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd("msh: cd : ", 2);
		ft_putstr_fd(dest, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	else if (type == 3)
	{
		ft_putstr_fd("msh: cd : ", 2);
		ft_putstr_fd(dest, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	if (forked == 1)
		exit (1);// au dessus de exit // free_lex(pipex->env); puis // free_all(pipex); ??
	g_return_value = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:35:57 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 20:38:42 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_value_in_env(char *src, char **env)
{
	int	y;

	y = 0;
	while (env && env[y])
	{
		if (!ft_strncmp(src, env[y], ft_strlen(src)) && \
		env[y][ft_strlen(src)] == '=')
			return (true);
		y++;
	}
	return (false);
}

int	ft_unset(t_pipex *pipex, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**envl;
	char	*vari;

	i = 0;
	if (!cmd->arguments[1])
		return (SUCCESS);
	vari = cmd->arguments[1];
	if (!is_value_in_env(vari, pipex->env))
		return (SUCCESS);
	envl = pipex->env;
	pipex->env = ft_calloc(sizeof(char *), (count_line(envl)));
	if (pipex->env == NULL || !vari || cmd->arguments[2])
	{
		perror("Malloc error");
		exit(-1);
	}
	j = 0;
	while (envl[i] != NULL)
	{
		if (!ft_strncmp(vari, envl[i], ft_strlen(vari)) && \
		envl[i][ft_strlen(vari)] == '=')
		{
			i++;
			continue ;
		}
		pipex->env[j] = ft_strdup(envl[i]);
		if (pipex->env[j] == NULL)
		{
			free_lex(pipex->env);
			perror("Malloc error");
			exit(-1);
		}
		i++;
		j++;
	}
	i++;
	free_tab(envl);
	return (SUCCESS);
}

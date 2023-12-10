/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:36:04 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 11:50:08 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	var_exist_n_replace(t_pipex *pipex, char *src)
{
	int		y;
	char	**s;

	y = 0;
	s = ft_split(src, '=');
	while (pipex->env && pipex->env[y])
	{
		if (!ft_strncmp(s[0], pipex->env[y], ft_strlen(s[0])) && \
		pipex->env[y][ft_strlen(s[0])] == '=')
		{
			free(pipex->env[y]);
			pipex->env[y] = ft_strdup(src);
			free_tab2(s);
			return (true);
		}
		y++;
	}
	free_tab2(s);
	return (false);
}

int	handle_no_argument(t_cmd *cmd)
{
	return (!cmd->arguments[1] ? SUCCESS : 0);
}

int	copy_environment(t_pipex *pipex, char **envl)
{
	int i = 0;
	while (envl[i] != NULL)
	{
		pipex->env[i] = ft_strdup(envl[i]);
		if (pipex->env[i] == NULL)
		{
			free_lex(pipex->env);
			perror("Malloc error");
			exit(-1);
		}
		i++;
	}
	return i;
}

int	ft_export(t_pipex *pipex, t_cmd *cmd)
{
	if (handle_no_argument(cmd))
		return (SUCCESS);

	char	**envl = pipex->env;
	char	*vari = cmd->arguments[1];

	if (!vari || !ft_strchr(vari, '=') || var_exist_n_replace(pipex, vari) || cmd->arguments[2])
		return (0);

	pipex->env = ft_calloc(sizeof(char *), (count_line(envl) + 2));
	if (pipex->env == NULL)
	{
		perror("Malloc error");
		exit(-1);
	}

	int i = copy_environment(pipex, envl);

	pipex->env[i] = ft_strdup(vari);
	i++;

	free_tab(envl);
	return (SUCCESS);
}

// int	ft_export(t_pipex *pipex, t_cmd *cmd)
// {
// 	int		i;
// 	char	**envl;
// 	char	*vari;

// 	i = 0;
// 	if (!cmd->arguments[1])
// 		return (SUCCESS);
// 	vari = cmd->arguments[1];
// 	if (!ft_strchr(vari, '='))
// 		return (0);
// 	if (var_exist_n_replace(pipex, vari))
// 		return (0);
// 	envl = pipex->env;
// 	pipex->env = ft_calloc(sizeof(char *), (count_line(envl) + 2));
// 	if (pipex->env == NULL || !vari || cmd->arguments[2])
// 	{
// 		perror("Malloc error");
// 		exit(-1);
// 	}
// 	while (envl[i] != NULL)
// 	{
// 		pipex->env[i] = ft_strdup(envl[i]);
// 		if (pipex->env[i] == NULL)
// 		{
// 			free_lex(pipex->env);
// 			perror("Malloc error");
// 			exit(-1);
// 		}
// 		i++;
// 	}
// 	pipex->env[i] = ft_strdup(vari);
// 	i++;
// 	free_tab(envl);
// 	return (SUCCESS);
// }

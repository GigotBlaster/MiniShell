/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:36:10 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 19:19:57 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **e)
{
	int	i;

	i = 0;
	while (e && e[i])
	{
		if (ft_strchr(e[i], '=') != NULL && ft_strchr(e[i], '=') != e[i])
			ft_printf("%s\n", e[i]);
		i++;
	}
}

int	ft_env(t_pipex *env, t_cmd *cmd)
{
	if (cmd->arguments[1])
	{
		ft_printf_fd(2, "Too many arguments\n");
		g_return_value = 999;
		return (g_return_value);
	}
	printf("je suis passee par laaaaaa\n");
	print_env(env->env);
	g_return_value = 0;
	return (g_return_value);
}

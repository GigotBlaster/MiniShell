/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:36:10 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 20:29:19 by npetitpi         ###   ########.fr       */
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
		return (EXIT_FAILURE);
	}
	printf("je suis passee par laaaaaa\n");
	print_env(env->env);
	return (SUCCESS);
}

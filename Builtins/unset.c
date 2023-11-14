/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:35:57 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/14 14:35:58 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_one(char *to_unset, t_list *envl)
{
	t_list	*previous;

	previous = envl;
	envl = envl->next;
	while (envl)
	{
		if (variable_match(envl, to_unset, 0))
		{
			previous->next = envl->next;
			free_entry(envl->content);
			free(envl);
			return ;
		}
		previous = envl;
		envl = envl->next;
	}
}

int			ft_unset(t_info *cmd, t_list **envl)
{
	int		i;
	int		ret;

	if (cmd->number <= 1)
		return (0);
	i = cmd->offset + 1;
	ret = SUCCESS;
	while (cmd->argv[i])
	{
		if (authorized_char(cmd->argv[i]) && !ft_strchr(cmd->argv[i], '='))
			unset_one(cmd->argv[i], *envl);
		else
		{
			invalid_identifier(cmd->argv[i], "unset", 1);
			ret = ERROR;
		}
		i++;
	}
	return (ret);
}

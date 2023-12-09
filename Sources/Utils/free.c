/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:37:51 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 13:38:28 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	args = 0;
}

void	free_tab2(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmd_ln(t_cmd *cmd)//rn
{
	free(cmd->redirection);
	free_tab2(cmd->fichiers);
	free_tab2(cmd->arguments);
	free(cmd);
}

void	*ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

void	ft_freeredir(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->fichiers[i])
		ft_free((void **)&cmd->fichiers[i++]);
	ft_free((void **)&cmd->redirection);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:37:51 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 10:28:02 by npetitpi         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)//rn
{
	free(cmd->redirection);
	cmd->redirection = NULL;
	free_tab2(cmd->fichiers);
	cmd->fichiers = NULL;
	free_tab2(cmd->arguments);
	cmd->arguments = NULL;
	free(cmd);
	cmd = NULL;
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

void free_pipex(t_pipex *pipex)
{
	free_tab2(pipex->cmds);
	pipex->cmds = NULL;
	free(pipex->buf);
	pipex->buf = NULL;
	free(pipex->pid);
	pipex->pid = NULL;
	free_tab2(pipex->env);
	pipex->env = NULL;
	free(pipex->stop);
	pipex->env = NULL;
}

void free_all(t_pipex *pipex, t_cmd *cmd)
{
	free_pipex(pipex);
	free_cmd(cmd);
}

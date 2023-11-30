/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:37:51 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 15:12:08 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_all(char *line, t_split *split)
{
	int	i;

	(void)line;
	if (line)
		free(line);
	if (!split)
		return ;
	i = 0;
	while (split[i].str)
	{
		free(split[i].str);
		i++;
	}
	free(split);
}

void		free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->info)
	{
		free_cmd(tree->info);
		close_unused_fd(tree->info);
		free(tree->info);
	}
	if (tree)
		free(tree);
}

void	free_entry(void *ventry)
{
	t_env	*entry;

	entry = (t_env *)ventry;
	if (entry->var)
		free(entry->var);
	if (entry->value)
		free(entry->value);
	free(entry);
}

static void	free_cmd(t_info *cmd)
{
	if (cmd->args)
		free_tab(cmd->args);
	if (cmd->argv)
		free(cmd->argv);
	if (cmd->env)
		free_tab(cmd->env);
	if (cmd->seps)
		free(cmd->seps);
	if (cmd->spaces)
		free(cmd->spaces);
	if (cmd->args_tmp)
		free_tab(cmd->args_tmp);
	if (cmd->seps_tmp)
		free(cmd->seps_tmp);
	if (cmd->spaces_tmp)
		free(cmd->spaces_tmp);
}

void		free_tab(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

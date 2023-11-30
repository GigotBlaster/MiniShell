/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:29:10 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 13:29:11 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		authorized_char(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && (s[0] != '_'))
		return (0);
	while (s[i] && (s[i] != '='))
	{
		if (!ft_isalnum(s[i]) && (s[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}
static char	*ft_strcut(char *line, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (line[i] && line[i] != c)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int			variable_match(t_list *envl, char *var, int cut)
{
	char	*env_var;
	char	*to_find;

	if (cut)
		to_find = ft_strcut(var, '=');
	else
		to_find = ft_strdup(var);
	env_var = ((t_env *)envl->content)->var;
	if (ft_strcmp(env_var, to_find) == 0)
	{
		free(to_find);
		return (1);
	}
	free(to_find);
	return (0);
}


void		ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;
	void	*save;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = list_size(*begin_list);
	while (i < size)
	{
		j = 0;
		current = *begin_list;
		while (j < size - 1 - i)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				save = current->content;
				current->content = current->next->content;
				current->next->content = save;
			}
			current = current->next;
			j++;
		}
		i++;
	}
}

void	close_unused_fd(t_info *cmd)
{
	if (cmd->input != STDIN && cmd->input != -1)
		close(cmd->input);
	if (cmd->output != STDOUT && cmd->output != -1)
		close(cmd->output);
}

int			list_size(t_list *begin_list)
{
	int		i;

	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:46:21 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 16:05:54 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*token(char *str)
{
	char	**input;
	t_cmd	*cmd;
	int		i;

	i = 0;
	input = ft_split(str, ' ');
	if (!input)
		return (NULL);
	while (input[i])
	{
		ft_remove_quote(input[i]);
		ft_restore(input[i]);
		i++;
	}
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (free_tab2(input), NULL);
	if (!token2(input, cmd))
		return (NULL);
		// free_tab2(input);
		// free_cmd_ln(cmd);
	return (cmd);
}

t_cmd	*token2(char **input, t_cmd *cmd)
{
	int	i;
	int	red_nb;
	int	args_nb;

	i = 0;
	red_nb = 0;
	args_nb = 0;
	while (input[i])
	{
		if (is_a_redirection(input[i]))
			red_nb++;
		else
			args_nb++;
		i++;
	}
	cmd->redirection = ft_calloc(sizeof(int), red_nb + 1);
	if (!cmd->redirection)
		return (free_tab2(input), free_cmd_ln(cmd), NULL);
	cmd->fichiers = ft_calloc(sizeof(char *), red_nb + 1);
	if (!cmd->fichiers)
		return (free_tab2(input), free_cmd_ln(cmd), NULL);
	cmd->arguments = ft_calloc(sizeof(char *), args_nb + 1);
	if (!cmd->arguments)
		return (free_tab2(input), free_cmd_ln(cmd), NULL);
	return (token3(input, cmd));
}

t_cmd	*token3(char **input, t_cmd *cmd)
{
	int	i;
	int	r;
	int	a;

	i = -1;
	r = 0;
	a = 0;
	while (input[++i])
	{
		if (is_a_redirection(input[i]))
		{
			//printf("%s\n", input[i]); // oust
			cmd->redirection[r] = is_a_redirection(input[i]);
			if (!input[i + 1])
            {
                // printf("ambiguous redirect\n"); // oust
                return free_cmd_ln(cmd), NULL;
            }
			cmd->fichiers[r] = ft_strdup(input[++i]);
			if (!cmd->fichiers[r++])
				return (free_cmd_ln(cmd), NULL);
		}
		else
		{
			cmd->arguments[a] = ft_strdup(input[i]);
			if (!cmd->arguments[a++])
				return (free_cmd_ln(cmd), NULL);
		}
	}
	cmd->command = cmd->arguments[0];
	return (cmd);
}

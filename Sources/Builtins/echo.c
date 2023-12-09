/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:02:12 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 20:28:00 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	no_newline;

	// printf("-----------MON ECHO--------------- \n");
	i = 1;
	no_newline = 0;
	while (cmd->arguments[i] && strcmp(cmd->arguments[i], "-n") == 0)
	{
		no_newline++;
		i++;
	}
	while (cmd->arguments[i])
	{
		printf("%s", cmd->arguments[i]);
		i++;
		if (cmd->arguments[i])
			printf(" ");
	}
	if (!no_newline)
		printf("\n");
}

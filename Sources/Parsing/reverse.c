/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:57:55 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 12:06:22 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reverse(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == SQ || line[i] == DQ)
			line[i] = line[i] * -1;
		i++;
	}
}

void	ft_restore(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			line[i] = -line[i];
		i++;
	}
}

void	ft_reverse_all(char *line)
{
	int	i;
	int	context;

	context = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == context)
			context = 0;
		else if (!context && line[i] == DQ)
			context = DQ;
		else if (!context && line[i] == SQ)
			context = SQ;
		else if (context == SQ || context == DQ)
		{
			if (line[i] > 0)
				line[i] *= -1;
		}
		i++;
	}
}

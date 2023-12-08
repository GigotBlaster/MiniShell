/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:29:10 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/05 18:43:39 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*noquote(char *str)
{
	char	*result;
	char	*write;

	result = str;
	write = str;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			char c = *str;
			str++;
			while (*str != c)
				*write++ = *str++;
			str++;
		}
		*write++ = *str++;
	}
	*write = '\0';
	return (result);
}

void ft_remove_quote(char *str)
{
	int i = 0;
	int j = 0;

	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

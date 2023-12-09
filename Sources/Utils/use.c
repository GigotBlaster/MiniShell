/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:29:10 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 12:58:53 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*noquote(char *str)
{
	char	*result;
	char	*write;
	char	c;

	result = str;
	write = str;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			c = *str;
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

void	ft_remove_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

void	dupclose(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

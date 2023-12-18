/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:58:23 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/11 12:59:18 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_1(char *str, int *wc)
{
	int i = 0;
	
	while (str[i])
	{
		while (str[i] && (str[i] == '|'))
			i++;
		if (str[i])
			(*wc)++;
		while (str[i] && (str[i] != '|'))
			i++;
	}
	return str;
}

char	*ft_strncpy_custom(char *dest, char *src, int start, int end)
{
	int i = 0;

	while (start + i < end)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char	**split_2(char *str, int wc)
{
	int		i = 0;
	int		j;
	int		k = 0;
	char	**out;

	out = (char **)malloc(sizeof(char *) * (wc + 1));
	while (str[i])
	{
		while (str[i] && (str[i] == '|'))
			i++;
		j = i;
		while (str[i] && (str[i] != '|'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * (i - j + 1));
			ft_strncpy_custom(out[k++], str, j, i);
		}
	}
	out[k] = NULL;
	return out;
}

char	**ft_split_pipe(char *str, int *wc)
{
	str = split_1(str, wc);
	return split_2(str, *wc);
}
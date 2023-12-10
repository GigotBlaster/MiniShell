/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:31:02 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 17:15:14 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libftfull.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strncpysplit(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

char	**ft_split2(char *str, char c, int wc)
{
	char	**out;
	int		j;
	int		i;
	int		k;

	j = 0;
	k = 0;
	out = (char **)malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		j = i;
		while (str[i] && (str[i] != c))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpysplit(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}

void	count_words(char *str, char c, int *wc)
{
	int i;

	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i])
			(*wc)++;
		while (str[i] && (str[i] != c))
			i++;
	}
}

char	**ft_split(char *str, char c)
{
	int	wc;

	wc = 0;
	count_words(str, c, &wc);
	return (ft_split2(str, c, wc));
}

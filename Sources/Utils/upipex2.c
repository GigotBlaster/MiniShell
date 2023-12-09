/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upipex2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:14:38 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 12:47:28 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pipexstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = ((char *)malloc(sizeof(char) * (ft_pipexstrlen(s1) + \
	ft_pipexstrlen(s2) + 1)));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	ft_pipexstrncmp(char *str1, char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)str1[i] == str2[i] && (i < n - 1)
		&& (unsigned char)str1[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

char	**ft_pipexsplit2(const char *s, char c, char **strs, int nb_words)
{
	int	i;
	int	j;
	int	words_index;

	i = 0;
	words_index = 0;
	while (words_index < nb_words)
	{
		while (s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		strs[words_index] = (char *)malloc(sizeof(char) * (j + 1));
		if (!strs[words_index])
		{
			ft_pipexfree(strs, words_index);
			return (NULL);
		}
		ft_pipexstrlcpy(strs[words_index], &(s[i]), j + 1);
		i += j;
		words_index++;
	}
	strs[words_index] = NULL;
	return (strs);
}

char	**ft_pipexsplit(char *s, char c)
{
	char	**strs;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_counter(s, c);
	strs = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!strs)
		return (NULL);
	return (ft_pipexsplit2(s, c, strs, nb_words));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:32:14 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 13:51:57 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

// char	*ft_strdup(const char *s)
// {
// 	size_t	l;
// 	size_t	i;
// 	char	*dup;

// 	l = ft_strlen(s);
// 	dup = malloc(sizeof(char) * (l + 1));
// 	i = -1;
// 	if (!dup)
// 		return (NULL);
// 	while (++i < l)
// 		dup[i] = s[i];
// 	dup[i] = '\0';
// 	return (dup);
// }

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	index;

	index = 0;
	dup = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (0);
	while (src[index])
	{
		dup[index] = src[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:32:51 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/29 23:29:30 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]) && (i < n))
// 		i++;
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 	return (0);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i < n)
		return (str1[i] - str2[i]);
	return (0);
}

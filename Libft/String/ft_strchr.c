/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:31:16 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:31:17 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	n;
	size_t	i;
	char	*str;

	n = ft_strlen(s);
	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	if (c == 0)
		return (str + n);
	return (NULL);
}

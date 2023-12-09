/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:32:21 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 20:01:28 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t	d;
	size_t	i;

	d = ft_strlen(dst);
	i = 0;
	if (dst[i] == '\0')
		return (NULL);
	while (src[i])
	{
		dst[d + i] = src[i];
		i++;
	}
	return (dst);
}

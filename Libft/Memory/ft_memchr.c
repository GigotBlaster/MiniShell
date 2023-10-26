/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:14:42 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 15:14:43 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	mem = (unsigned char *)s;
	i = -1;
	while (++i < n)
	{
		if (mem[i] == (unsigned char)c)
			return (mem + i);
	}
	return (NULL);
}

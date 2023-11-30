/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:14:56 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 13:49:39 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

// void	*ft_memset(void *s, int c, size_t n)
// {
// 	unsigned char	*mem;
// 	size_t			i;

// 	mem = (unsigned char *)s;
// 	i = -1;
// 	while (++i < n)
// 		mem[i] = (unsigned char)c;
// 	return (s);
// }

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;
	size_t			i;

	dst = s;
	i = 0;
	while (i < n)
	{
		dst[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
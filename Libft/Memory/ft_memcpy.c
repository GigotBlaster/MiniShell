/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:14:48 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 15:14:49 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*mem;
	unsigned char	*str;
	size_t			i;

	if (dest == 0 && src == 0)
		return (0);
	mem = (unsigned char *)dest;
	str = (unsigned char *)src;
	i = -1;
	while (++i < n)
		mem[i] = str[i];
	return (dest);
}

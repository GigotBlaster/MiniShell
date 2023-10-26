/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:14:31 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 15:14:32 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char *)s;
	i = -1;
	while (++i < n)
		mem[i] = '\0';
	return (s);
}

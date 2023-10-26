/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:14:35 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 15:14:36 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*mem;
	size_t			s;
	size_t			i;

	s = nmemb * size;
	ptr = malloc(s);
	if (!ptr)
		return (NULL);
	mem = (unsigned char *)ptr;
	i = -1;
	while (++i < s)
		mem[i] = '\0';
	return (ptr);
}

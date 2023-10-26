/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:23:24 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:57:41 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

static int	utoa_size(unsigned int nb)
{
	if (nb < 10)
		return (1);
	return (1 + utoa_size(nb / 10));
}

char	*ft_utoa(unsigned int n)
{
	char			*res;
	int				i;
	int				l;

	l = utoa_size(n);
	res = malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	if (n == 0)
		res[0] = '0';
	i = l - 1;
	while (i >= 0)
	{
		res[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:23:01 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:57:35 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

static int	itoa_size(unsigned int nb, short int sg)
{
	if (nb < 10)
		return (1 + (sg == -1));
	return (1 + itoa_size(nb / 10, sg));
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	short int		sg;
	char			*res;
	int				i;
	int				l;

	sg = 1 - 2 * (n < 0);
	nb = sg * n;
	l = itoa_size(nb, sg);
	res = malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	if (n == 0)
		res[0] = '0';
	if (sg == -1)
		res[0] = '-';
	i = l - 1;
	while (i >= (sg == -1))
	{
		res[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (res);
}

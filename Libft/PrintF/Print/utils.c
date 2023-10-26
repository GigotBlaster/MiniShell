/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:45:25 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:56:26 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

char	*ft_ptoa(unsigned long ptr, int size)
{
	char	*res;
	char	*base;
	int		i;

	base = "0123456789abcdef";
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[size] = '\0';
	i = size;
	while (--i > 1)
	{
		res[i] = base[ptr % 16];
		ptr = ptr / 16;
	}
	res[0] = '0';
	res[1] = 'x';
	return (res);
}

int	size_ptr(unsigned long ptr, int prec)
{
	int		i;

	i = 0;
	if (ptr == 0)
		return (ft_max(1, prec) + 2);
	while (ptr > 0)
	{
		ptr = ptr / 16;
		i++;
	}
	return (ft_max(i, prec) + 2);
}

int	min_not_neg(int a, int b)
{
	if (a == -1)
		return (b);
	if (a < b)
		return (a);
	return (b);
}

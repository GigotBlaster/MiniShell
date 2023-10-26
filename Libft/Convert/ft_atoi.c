/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:17:42 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 14:00:31 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

static int	is_space(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long int	nb;
	short int				atoi;

	nb = 0;
	while (*nptr && is_space(*nptr))
		nptr++;
	atoi = 1 - 2 * (*nptr == '-');
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && ft_isdigit(*nptr))
	{
		nb = 10 * nb + (*nptr - 48);
		if (nb > (unsigned long long)(9223372036854775807 + (atoi == -1)))
			return ((atoi + 1) / (-2));
		nptr++;
	}
	return ((int)(atoi * nb));
}

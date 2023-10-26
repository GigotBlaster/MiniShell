/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:16:27 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:16:28 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <unistd.h>

void	ft_putstr(char *s)
{
	size_t	l;

	if (!s)
		return ;
	l = ft_strlen(s);
	write(1, s, l);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:16:09 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:16:10 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <unistd.h>

void	ft_putendl(char *s)
{
	size_t	l;

	if (!s)
		return ;
	l = ft_strlen(s);
	write(0, s, l);
	write(0, "\n", 1);
}

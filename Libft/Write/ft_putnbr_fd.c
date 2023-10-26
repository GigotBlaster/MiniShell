/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:16:14 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:50:15 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

static void	rec_putnbr_fd(unsigned int nb, int fd, int sg)
{
	if (nb == 0)
	{
		if (sg == -1)
			ft_putchar_fd('-', fd);
		return ;
	}
	rec_putnbr_fd(nb / 10, fd, sg);
	ft_putchar_fd(nb % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	short int		sg;

	sg = 1 - 2 * (n < 0);
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
		rec_putnbr_fd(sg * n, fd, sg);
}

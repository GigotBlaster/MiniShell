/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_7hexx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:44:55 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:44:56 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_7hxx(t_print param, va_list args)
{
	unsigned int	nb;
	int				size;
	char			*nb_utoxx;
	char			*to_print;

	nb = (unsigned int)va_arg(args, int);
	nb_utoxx = ft_utoxx(nb);
	if (nb == 0 && param.precision == 0)
		nb_utoxx[0] = '\0';
	size = size_int(param, nb_utoxx);
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_int(&to_print, nb_utoxx, param, size);
	free(nb_utoxx);
	ft_putstr_fd(to_print, param.fd);
	free(to_print);
	return (size - 1);
}

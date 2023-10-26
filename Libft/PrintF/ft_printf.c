/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:45:46 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:45:48 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_print	param;
	int		nb_char;

	if (!is_all_coherent(str))
		return (0);
	va_start(args, str);
	nb_char = 0;
	while (*str)
	{
		if (*str != '%')
			str = print_str_classic(str, &nb_char, 1);
		else
		{
			str++;
			init_param(&param);
			str = parse_param(&param, str, args);
			if (!str)
				return (0);
			param.fd = 1;
			print_param(param, args, &nb_char);
		}
	}
	va_end(args);
	return (nb_char);
}

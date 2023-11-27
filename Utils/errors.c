/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:04:36 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/27 15:03:00 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *exe, char *file, int err, char *error)
{
	if (!error)
		ft_putstr_fd("minishell: ", STDERR);
	if (file)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (exe)
	{
		ft_putstr_fd(exe, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (error)
		ft_putstr_fd(error, STDERR);
	else
		ft_putstr_fd(strerror(err), STDERR);
	ft_putstr_fd("\n", STDERR);
}

int		error_msg(int error)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (error == ALLOCATION_FAIL)
		ft_putstr_fd("allocation failed\n", STDERR);
	else if (error == FORK_FAIL)
		ft_putstr_fd("fork failed\n", STDERR);
	return (ERROR);
}

void	invalid_identifier(char *str, char *func, int exported)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (func && exported)
	{
		ft_putstr_fd(func, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	write(STDERR, "`", 1);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
}
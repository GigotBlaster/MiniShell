/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:02:12 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 12:05:42 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args, int option, int i)
{
	while (args[i] && args[i + 1])
	{
		ft_putstr(args[i]);
		ft_putstr(" ");
		i++;
	}
	if (args[i])
		ft_putstr(args[i]);
	if (!option)
		ft_putstr("\n");
}

static int	echo_option(t_info *cmd)
{
	int	i;

	i = 1;
	while ((cmd->args)[i] && (ft_strcmp((cmd->args)[i], "-n") == 0))
		i++;
	return (i);
}

int	ft_echo(t_info *cmd, t_list **envl)
{
	int i;
	int pid;

	(void)envl;
	i = echo_option(cmd);
	pid = fork();
	if (pid == -1)
		return (error_msg(FORK_FAIL));
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		print_args(cmd->argv + cmd->offset, (i > 1), i);
		exit(SUCCESS);
	}
	return (SUCCESS);
}

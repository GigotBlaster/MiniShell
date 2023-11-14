/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:30:06 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/07 16:04:52 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//PDW : Print Working Directory
//
#include "minishell.h"

void	change_stdin_stdout(t_info *cmd)
{
	if (cmd->output != STDOUT)
	{
		close(STDOUT);
		dup(cmd->output);
	}
	if (cmd->input != STDIN)
	{
		close(STDIN);
		dup(cmd->input);
	}
}

int ft_pdw(t_info *cmd, t_list **envl)
{
	char	cwd[SIZE_PATH];
	int		pid;

	(void)envl;
	getcwd(cwd, SIZE_MAX);
	pid = fork();
	if (pid == -1)	
		return(error_msg(FORK_FAIL));
	else if (pid == 0)
	{
		change_stdin_stdout(cmd);
		ft_putstr(cwd);
		ft_putstr("\n");
		exit(SUCCESS);
	}
	return (SUCCESS);
}
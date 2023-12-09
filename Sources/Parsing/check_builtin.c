/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:48:47 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 19:28:42 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built_in_baby(t_pipex *p, char *str) //suz
{
	t_cmd	*cmd;

	cmd = token(str);
	if (!cmd || !cmd->arguments || !cmd->arguments[0])
		return (SUCCESS);
	if (ft_strncmp(cmd->arguments[0], "pwd", 4) == 0)
	{
		ft_pwd(cmd);
		return (1);
	}
	if (ft_strncmp(cmd->arguments[0], "env", 4) == 0)
	{
		ft_env(p, cmd);
		return (1);
	}
	if (ft_strncmp(cmd->arguments[0], "echo", 5) == 0)
	{
		ft_echo(cmd);
		return (1);
	}
	return (0);
}

int	check_built_in_dad(t_pipex *p, char *str)//suz
{
	t_cmd	*cmd;

	cmd = token(str);
	if (!cmd || !cmd->arguments || !cmd->arguments[0]){
		// printf("la\n"); // oust
		return (0);
	}
	if (ft_strncmp(cmd->arguments[0], "cd", 3) == 0)
	{
		ft_cd(p, cmd, 0);
		printf("------------->%d\n", g_return_value);
		return (1);
	}
	else if (ft_strncmp(cmd->arguments[0], "export", 6) == 0)
	{
		ft_export(p, cmd);
		return (1);
	}
	else if (ft_strncmp(cmd->arguments[0], "unset", 6) == 0)
	{
		ft_unset(p, cmd);
		return (1);
	}
	else if (ft_strncmp(cmd->arguments[0], "exit", 5) == 0)
	{
		ft_exit(cmd, p->nbcmd);
		return (1);
	}
	return (0);
}

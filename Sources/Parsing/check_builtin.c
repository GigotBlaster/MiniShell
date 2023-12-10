/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:48:47 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 16:16:59 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built_in_baby(t_pipex *p, char *str)
{
	t_cmd	*cmd;

	cmd = token(str);
	if (!cmd || !cmd->arguments || !cmd->arguments[0])
	{
		//free_all(p, cmd);
		free_cmd(cmd);
		return (SUCCESS);
	}
	if (ft_strncmp(cmd->arguments[0], "pwd", 4) == 0)
		return (ft_pwd(cmd), free_cmd(cmd), 1);
	if (ft_strncmp(cmd->arguments[0], "env", 4) == 0)
		return (ft_env(p, cmd), free_cmd(cmd), 1);
	if (ft_strncmp(cmd->arguments[0], "echo", 5) == 0)
		return (ft_echo(cmd), free_cmd(cmd), 1);
	free_cmd(cmd);
	return (0);
}

int	check_built_in_dad(t_pipex *p, char *str)
{
	t_cmd	*cmd;

	cmd = token(str);
	if (!cmd || !cmd->arguments || !cmd->arguments[0])
	{
	//	free_all(p, cmd);
		free_cmd(cmd);
		return (0);
	}
	if (ft_strncmp(cmd->arguments[0], "cd", 3) == 0)
		return (ft_cd(p, cmd, 0), free_cmd(cmd), 1);
	else if (ft_strncmp(cmd->arguments[0], "export", 6) == 0)
		return (ft_export(p, cmd), free_cmd(cmd), 1);
	else if (ft_strncmp(cmd->arguments[0], "unset", 6) == 0)
		return (ft_unset(p, cmd), free_cmd(cmd), 1);
	else if (ft_strncmp(cmd->arguments[0], "env", 3) == 0)
		return (ft_env(p, cmd), free_cmd(cmd), 1);
	else if (ft_strncmp(cmd->arguments[0], "exit", 5) == 0)
		return (ft_exit(cmd, p), 1);
	free_cmd(cmd);
	return (0);
}

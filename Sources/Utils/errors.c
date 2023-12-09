/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:04:36 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 13:38:15 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errorcmd(t_info *data, t_cmd *cmd, char *str)
{
	(void) data;
	(void) str;
	ft_free((void **)&cmd->flag);
	ft_free((void **)&cmd->command);
	ft_freeredir(cmd);
}

void	error_fd(t_info *data, t_cmd *cmd, int i)
{
	if (errno == 13 && cmd->redirection[i] != 4)
		fprintf(stderr, "bash: %s: Permission denied\n", cmd->fichiers[i]);
	else if (cmd->redirection[i] != 4)
		fprintf(stderr, "bash: %s: No such file or directory\n",
			cmd->fichiers[i]);
	ft_errorcmd(data, cmd, "");
	close(data->fd[1]);
	close(data->fd[0]);
	exit(1);
}

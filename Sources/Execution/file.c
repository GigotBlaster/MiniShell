/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:01:53 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 17:05:37 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	file(t_info *data, t_cmd *cmd, int a) //with suz
{
	int	fd;
	int	i;
	int	fd_in;
	int	fd_out;

	i = 0;
	fd_in = -1;
	fd_out = -1;
	while (cmd->redirection[i])
	{
		printf("here\n");
		if (cmd->redirection[i] == 1)
			fd = open(cmd->fichiers[i], O_TRUNC | O_WRONLY | O_CREAT, 0666);
		else if (cmd->redirection[i] == 2)
			fd = open(cmd->fichiers[i], O_APPEND | O_WRONLY | O_CREAT, 0666);
		else if (cmd->redirection[i] == 3)
			fd = open(cmd->fichiers[i], O_RDONLY);
		else if (cmd->redirection[i] == 4)
		{
			fd = open(".tmp_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (fd < 0)
				perror("ERROR CAN't open FD:");
			ft_heredoc(fd, cmd->fichiers[i]);
			close(fd);
			fd = open(".tmp_heredoc", O_RDONLY);
			unlink(".tmp_heredoc");
		}
		else if (cmd->redirection[i] == 5)
			get_pipe(data->here, data);
		if (fd == -1)
			error_fd(data, cmd, a);
		else if (cmd->redirection[i] > 2 && cmd->redirection[i] < 5)
			fd_in = fd;
		else if (cmd->redirection[i] < 3)
		{
			fd_out = fd;
			dupclose(fd_out, STDOUT_FILENO);
		}
		fd = -1;
		i++;
	}
	if (fd_in > -1)
		dupclose(fd_in, STDIN_FILENO);
	else if (fd_out > -1)
		dupclose(fd_out, STDOUT_FILENO);
}

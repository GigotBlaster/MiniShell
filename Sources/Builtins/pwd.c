/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:30:06 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 20:36:18 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//PWD : Print Working Directory
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

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;
	int		fd;

	(void)cmd;
	fd = 1;
	cwd = getcwd(NULL, 0); // Récupère le rép actuel
	printf("MON PWD :)\n");
	if (cwd == NULL)
	{
		perror("pwd");
		return (12);
	}
	if (write(fd, cwd, ft_strlen(cwd)) == -1)
	{
		write(2, "pwd: write error: No space left on device\n", 43);
		free(cwd);
		return (1);
	}
	write(fd, "\n", 1);
	free(cwd);
	return (SUCCESS);
}

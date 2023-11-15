/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:30:06 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 15:46:02 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//PDW : Print Working Directory
//
#include "minishell.h"

 //gestion in out
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
    char cwd[SIZE_PATH];
    int pid;

    (void)envl; //no use

    getcwd(cwd, SIZE_MAX);  // Récupère le rép actuel
    pid = fork();  // Crée un child process

    if (pid == -1)
        return (error_msg(FORK_FAIL));  //erreur
    else if (pid == 0)
    {
        // Code exécuté par child process
        change_stdin_stdout(cmd);  // Change in out en fonction de cmd
        ft_putstr(cwd);  // Affiche le répertoire de travail actuel
        ft_putstr("\n");
        exit(SUCCESS);  // Termine chil process success
    }

    // Code exécuté par le processus parent
    return (SUCCESS);
}

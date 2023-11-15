/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:02:12 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 14:57:28 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args, int option, int i)
// imprime les éléments du tableau
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
	// trouve l'indice où le contenu de "echo" commence, sans - n.i++ jusqu'à arg != -n.
{
	int i;

	i = 1;
	while ((cmd->args)[i] && (ft_strcmp((cmd->args)[i], "-n") == 0))
		i++;
	return (i);
}

int	ft_echo(t_info *cmd, t_list **envl)
{
	int i;
	int pid;

	(void)envl;           // Evite warning variable no used
	i = echo_option(cmd); // Départ pour print args
	pid = fork();         // Crée new process

	if (pid == -1)
	{
		return (error_msg(FORK_FAIL)); // Erreur
	}
	else if (pid == 0)
	{
		// Code exécuté dans child process
		change_stdin_stdout(cmd);
		// Change in et out sortie standard selon les besoins de la commande
		print_args(cmd->argv + cmd->offset, (i > 1), i);
		// Print args à partir de i
		exit(SUCCESS);
		// Termine child process avec success
	}
	// Code exécuté dans le processus parent
	return (SUCCESS);
}

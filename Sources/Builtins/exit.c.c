/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:36:33 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 15:33:30 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum(char *str)//Verif nb
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	free_exit(t_info *cmd, t_list **envl)
{
	ft_putstr("exit\n");
	free_all(cmd->line, cmd->split);
	free_tree(cmd->root);
	ft_lstclear(envl, &free_entry);
}

int	ft_exit(t_info *cmd, t_list **envl)
{
	int	exit_value;

	// Si le nb arg < 2
    if (nb_args(cmd->argv) < 2)
    {
        // Récupère la valeur de "?begin" dans l'env
        exit_value = ft_atoi(search_in_env(*envl, "?begin"));
        free_exit(cmd, envl);
        exit(exit_value); // Quitte avec la valeur récupérée
    }
    // Sinon, si pas nb
    else if (!ft_isnum(cmd->argv[cmd->offset + 1]))
    {
        free_exit(cmd, envl);
        // erreur
        print_error("minishell: exit", NULL, 0, "numeric argument required");
        exit(MISUSE); // Quitte le programme avec un code d'erreur
    }
    // Sinon, si le nb > 2
    else if (nb_args(cmd->argv) > 2)
    {
        ft_putstr("exit\n"); // Affiche "exit"
        // Affiche erreur
        print_error("minishell: exit", NULL, 0, "too many arguments");
        return (ERROR); // Renvoie un code d'erreur
    }
    // Sinon (cas standard)
    exit_value = ft_atoi(cmd->argv[cmd->offset + 1]); // Convertit l'argument en entier
    free_exit(cmd, envl); // Libère les ressources
    exit(exit_value); // Quitte le programme avec la valeur convertie
}

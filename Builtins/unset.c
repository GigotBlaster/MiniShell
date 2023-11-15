/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:35:57 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 16:06:50 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//désactiver une variable d'env spécifique
static void	unset_one(char *to_unset, t_list *envl)
{
	t_list	*previous;

	previous = envl;
	envl = envl->next;
	while (envl)
	{
		if (variable_match(envl, to_unset, 0))
		{
			previous->next = envl->next;
			free_entry(envl->content);
			free(envl);
			return ;
		}
		previous = envl;
		envl = envl->next;
	}
}


int			ft_unset(t_info *cmd, t_list **envl)
{
	int		i;
	int		ret;
 	// check nb variable à désactiver < 1
	if (cmd->number <= 1)
		return (0);
	// Désactiver les variables d'env ++
	i = cmd->offset + 1;
	ret = SUCCESS; // Variable de retour, initialisée à SUCCES
	while (cmd->argv[i])
	{
		// check arg contient des caractères autorisés et != '='
		if (authorized_char(cmd->argv[i]) && !ft_strchr(cmd->argv[i], '='))
			unset_one(cmd->argv[i], *envl);// Désac la variable d'env
		else
		{
			 // erreur pour un identifiant invalide
			invalid_identifier(cmd->argv[i], "unset", 1);
			ret = ERROR; // Mettre à jour la variable de retour en cas d'erreur
		}
		i++;
	}
	return (ret); // Retourner le statut de l'opération unset
}

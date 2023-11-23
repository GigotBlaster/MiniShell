/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:36:20 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/22 17:36:45 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//CD : Current Directory
//
#include "minishell.h"

int	nb_args(char **args) // nb d'elem dans le tab de tab
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*search_in_env(t_list *envl, char *var)
	// Cherche variable d'env dans lchaine, renvoi sa valeur ou NULL
{
	while (envl)
	{
		if (ft_strcmp(((t_env *)envl->content)->var, var) == 0)
			return (((t_env *)envl->content)->value);
		envl = envl->next;
	}
	return (NULL);
}

static int	cd_home(t_list *envl)
	//change le rép de travail vers le rép défini par la var d'env "HOME".
{
	char *path_home;

	path_home = search_in_env(envl, "HOME");
	if (!path_home)
	{
		print_error("minishell: cd", NULL, 0, "HOME not set");
		return (ERROR);
	}
	errno = 0;
	if (chdir(path_home))
	{
		print_error("cd", path_home, errno, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	cd_before(t_list *envl)
	//change le rép de travail vers le rép précédent
{
	char *old_path;

	old_path = search_in_env(envl, "OLDPWD");
	if (!old_path)
	{
		print_error("minishell: cd", NULL, 0, "OLDPWD not set");
		return (ERROR);
	}
	errno = 0;
	ft_putstr_fd(old_path, STDERR);
	ft_putstr_fd("\n", STDERR);
	if (chdir(old_path))
	{
		print_error("cd", old_path, errno, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_cd(t_info *cmd, t_list **envl) // Implementation de cd
{
	int err;
	char *path;

	// Vérifie nb args
	if (nb_args(cmd->argv + cmd->offset) > 2)
	{
		print_error("minishell: cd", NULL, 0, "too many arguments");
		return (MISUSE);
	}
	// Check si y'a un chemin en argument
	if (cmd->args[cmd->offset + 1])
	{
		path = cmd->argv[cmd->offset + 1];
		// Si le chemin est "-", retourne au répertoire précédent
		errno = 0;
		if (ft_strcmp("-", path) == 0)
			return (cd_before(*envl));
		// Change le répertoire de travail vers le chemin spécifié
		err = chdir(path);
		if (err)
		{
			// Si échec du changement de répertoire, erreur
			print_error("cd", cmd->argv[cmd->offset + 1], errno, NULL);
			return (ERROR);
		}
		//Si le changement de rép réussit
		return (SUCCESS);
	}
	// Si aucun chemin n'est spécifié, retourne au rép HOME
	return (cd_home(*envl));
}

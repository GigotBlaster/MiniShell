/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:08:52 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 16:11:50 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//copier une entrée d'environnement
static void	*copy_entry(void *entry)
{
	t_env	*ventry;
	t_env	*res;

	ventry = (t_env *)entry;
	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->var = ft_strdup(ventry->var);
	res->value = NULL;
	if (ventry->value)
		res->value = ft_strdup(ventry->value);
	res->exported = ventry->exported;
	return (res);
}

//comparer deux entrées d'environnement lors du tri
static int	cmp_entry(void *data1, void *data2)
{
	char	*str1;
	char	*str2;

	str1 = ((t_env *)data1)->var;
	str2 = ((t_env *)data2)->var;
	if (str1 && str2)
		return (ft_strcmp(str1, str2));
	return (0);
}

int print_sorted(t_list *envl, t_info *cmd)
{
    t_list *sorted;
    int pid;

    // Création child process
    pid = fork();

    if (pid == -1)
        return (error_msg(FORK_FAIL));
    else if (pid == 0)
    {
        // Changement de in out standard selon la configuration
        change_stdin_stdout(cmd);
        // Création d'une liste triée en copiant chaque entrée de la liste d'origine
        sorted = ft_lstmap(envl, &copy_entry, &free_entry);
        // Tri de la liste avec comp
        ft_lstsort(&sorted, &cmp_entry);
        // print liste triée sur la sortie standard
        print_envl(sorted, 1);
        // free liste triée
        ft_lstclear(&sorted, &free_entry);
        // Fin child process avec success
        exit(SUCCESS);
    }

    // Retourne success au processus parent
    return (SUCCESS);
}
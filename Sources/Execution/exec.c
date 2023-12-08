/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:04:12 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 15:07:11 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_redirection(char *str)
{
	if (!strcmp(str, ">"))
		return (1);
	if (!strcmp(str, ">>"))
		return (2);
	if (!strcmp(str, "<"))
		return (3);
	if (!strcmp(str, "<<"))
		return (4);
	if (!strcmp(str, "|"))
		return (5);
	return (0);
}

void	free_tab2(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmd_ln(t_cmd *cmd)
{
	free(cmd->redirection);
	free_tab2(cmd->fichiers);
	free_tab2(cmd->arguments);
	free(cmd);
}

t_cmd *token(char *str)
{
    char **input;
    t_cmd *cmd;
    int i = 0;
    input = ft_split(str, ' ');
    if (!input)
        return NULL;
    while(input[i])
    {
        ft_remove_quote(input[i]);
        ft_restore(input[i]);
        i++;
    }
    
    cmd = ft_calloc(sizeof(t_cmd), 1);
    if (!cmd)
        return free_tab2(input), NULL;
    if (!token2(input, cmd)) {
        // free_tab2(input);
        // free_cmd_ln(cmd);
        return NULL;
    }
    return (cmd);
}

t_cmd *token2(char **input, t_cmd *cmd)
{
    int i = 0;
    int red_nb = 0;
    int args_nb = 0;
    while (input[i])
    {
        if (is_a_redirection(input[i]))
            red_nb++;
        else
            args_nb++;
        i++;
    }
    cmd->redirection = ft_calloc(sizeof(int), red_nb + 1);
    if (!cmd->redirection)
        return free_tab2(input), free_cmd_ln(cmd), NULL;
    cmd->fichiers = ft_calloc(sizeof(char *), red_nb + 1);
    if (!cmd->fichiers)
        return free_tab2(input), free_cmd_ln(cmd), NULL;
    cmd->arguments = ft_calloc(sizeof(char *), args_nb + 1);
    if (!cmd->arguments)
        return free_tab2(input), free_cmd_ln(cmd), NULL;
    return (token3(input, cmd));
}

t_cmd *token3(char **input, t_cmd *cmd)
{
    int i = 0;
    int r = 0;
    int a = 0;
    while (input[i])
    {
        if (is_a_redirection(input[i]))
        {
            cmd->redirection[r] = is_a_redirection(input[i]);
            printf("redirection[%d]-> %d\n", r, cmd->redirection[r]);
            cmd->fichiers[r] = ft_strdup(input[++i]);
            printf("fichiers[%d]-> %s\n", r, cmd->fichiers[r]);
            if (!cmd->fichiers[r++])
                return free_cmd_ln(cmd), NULL;
        }
        else
        {
            cmd->arguments[a] = ft_strdup(input[i]);
            printf("arguments[%d]-> %s\n", a, cmd->arguments[a]);
            if (!cmd->arguments[a++])
                return free_cmd_ln(cmd), NULL;
        }
        i++;
    }
    // free(cmd->redirection);
    // cmd->redirection = NULL;
    cmd->command = cmd->arguments[0];
    return cmd;
}






// t_cmd	*token(char *str)
// {
// 	int		i;
// 	char	**input;
// 	t_cmd	*cmd;
// 	int		red_nb;
// 	int		args_nb;
// 	int		r;
// 	int		a;

// 	// rajouter espaces derriere les <>
// 	// split selon les whitespaces : obtient qqch du style {ls}{-la}{>>}{out}{<}{in}
// 	input = ft_splitexec(str, ' ');
// 	if (!input)
// 		return (NULL);
// 	// si appelle la fonction token() depuis le main,
// 	// meme pas beoin de malloc la structure commande (peut passer son adresse)
// 	cmd = calloc(sizeof(t_cmd), 1);
// 	if (!cmd)
// 		return (free_tab2(input), NULL);
// 	/*  ------------------------ A METTRE DANS AUTRE FONCTION (NORME) ------------------*/
// 	// definit le nombre de redirections et d'arguments de commandes que l on va avoir a stocker
// 	i = 0;
// 	red_nb = 0;
// 	args_nb = 0;
// 	while (input[i])
// 	{
// 		if (is_a_redirection(input[i]))
// 		{
// 			red_nb++;
// 			i++;
// 		}
// 		else
// 			args_nb++;
// 		i++;
// 	}
// 	// alloue l esoace memoire necessaire pour les types de redirections
// 	cmd->redirections = calloc(sizeof(int), red_nb);
// 	if (!cmd->redirections)
// 	{
// 		return (free_tab2(input), NULL);
// 	}
// 	// alloue l espace memoire necessaire pour les fichiers correspondant a chaque redirection
// 	cmd->fichiers = calloc(sizeof(char *), red_nb + 1);
// 	if (!cmd->fichiers)
// 		return (free_cmd_ln(cmd), NULL);
// 	cmd->arguments = calloc(sizeof(char *), args_nb + 1);
// 	if (!cmd->arguments)
// 		return (free_cmd_ln(cmd), NULL);
// 	/*  ------------------------- FIN DE LA SOUS-FONCTION ----------------------------- */
// 	i = 0;
// 	r = 0;
// 	a = 0;
// 	while (input[i])
// 	{
// 		if (is_a_redirection(input[i]))
// 		{
// 			cmd->redirections[r] = is_a_redirection(input[i]);
// 			cmd->fichiers[r] = strdup(input[++i]);
// 			if (!cmd->fichiers[r++])
// 				return (free_cmd_ln(cmd), NULL);
// 		}
// 		else
// 		{
// 			cmd->arguments[a] = strdup(input[i]);
// 			if (!cmd->arguments[a++])
// 				return (free_cmd_ln(cmd), NULL);
// 		}
// 		i++;
// 	}
// 	cmd->command = cmd->arguments[0];
// 	return (cmd);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:09:23 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/29 12:52:46 by ibouhssi         ###   ########.fr       */
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
	int	i;

	i = 0;
	free(cmd->redirections);
	free_tab2(cmd->fichiers);
	free_tab2(cmd->arguments);
	free(cmd->command);
	free(cmd);
}

t_cmd	*token(char *str)
{
	int		i;
	char	**input;
	t_cmd	*cmd;
	int		red_nb;
	int		args_nb;
	int		r;
	int		a;

	// rajouter espaces derriere les <>
	// split selon les whitespaces : obtient qqch du style {ls}{-la}{>>}{out}{<}{in}
	input = ft_split(str, " \t");
	if (!input)
		return (NULL);
	// si appelle la fonction token() depuis le main,
	// meme pas beoin de malloc la structure commande (peut passer son adresse)
	cmd = calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (free_tab2(input), NULL);
	/*  ------------------------ A METTRE DANS AUTRE FONCTION (NORME) ------------------*/
	// definit le nombre de redirections et d'arguments de commandes que l on va avoir a stocker
	i = 0;
	red_nb = 0;
	args_nb = 0;
	while (input[i])
	{
		if (is_a_redirection(input[i]))
		{
			red_nb++;
			i++;
		}
		else
			args_nb++;
		i++;
	}
	// alloue l esoace memoire necessaire pour les types de redirections
	cmd->redirections = calloc(sizeof(int), red_nb);
	if (!cmd->redirections)
	{
		return (free_tab2(input), NULL);
	}
	// alloue l espace memoire necessaire pour les fichiers correspondant a chaque redirection
	cmd->fichiers = calloc(sizeof(char *), red_nb + 1);
	if (!cmd->fichiers)
		return (free_cmd_ln(cmd), NULL);
	cmd->arguments = calloc(sizeof(char *), args_nb + 1);
	if (!cmd->arguments)
		return (free_cmd_ln(cmd), NULL);
	/*  ------------------------- FIN DE LA SOUS-FONCTION ----------------------------- */
	r = 0;
	a = 0;
	i = 0;
	while (input[i])
	{
		if (is_a_redirection(input[i]))
		{
			cmd->redirections[r] = is_a_redirection(input[i]);
			cmd->fichiers[r] = strdup(input[++i]);
			if (!cmd->fichiers[r++])
				return (free_cmd_ln(cmd), NULL);
		}
		else
		{
			cmd->arguments[a] = strdup(input[i]);
			if (!cmd->arguments[a++])
				return (free_cmd_ln(cmd), NULL);
		}
		i++;
	}
	cmd->command = cmd->arguments[0];
	return (cmd);
}

/*  ------------------- fonction d affichage ----------------------------- */

// void	print_cmd(t_cmd *cmd)
// {
// 	for (int i = 0; cmd->fichiers[i]; i++)
// 	{
// 		fprintf(stderr, "redirection %d, type is %d\n", i,
// 				cmd->redirections[i]);
// 		fprintf(stderr, "redirected in/from : %s\n", cmd->fichiers[i]);
// 	}
// 	fprintf(stderr, "command name : %s\n", cmd->command);
// 	for (int i = 0; cmd->arguments[i]; i++)
// 	{
// 		fprintf(stderr, "argument %d, value is %s\n", i, cmd->arguments[i]);
// 	}
// }

// int	main(int ac, char **av)
// {
// 	t_cmd *cmd;
// 	cmd = token(av[1]);
// 	print_cmd(cmd);
// }
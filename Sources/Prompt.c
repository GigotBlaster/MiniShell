/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:56:28 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 18:36:40 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	header(void)
{
	ft_putstr("\033[1;33m  __  __ _       _     _          _ _\n");
	ft_putstr(" |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
	ft_putstr(" | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
	ft_putstr(" | |  | | | | | | \\__ \\ | | |  __/ | |\n");
	ft_putstr(" |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n\n");
}

char	**ft_split_pipe(char *str, int *wc)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '|'))
			i++;
		if (str[i])
			(*wc)++;
		while (str[i] && (str[i] != '|'))
			i++;
	}
	char **out = (char **)ft_calloc(sizeof(char *), ((*wc) + 1));
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '|'))
			i++;
		j = i;
		while (str[i] && (str[i] != '|'))
			i++;
		if (i > j)
		{
			out[k] = (char *)ft_calloc(sizeof(char), ((i - j) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	return (out);
}


void	prompt(t_info	*info)
{
	static t_pipex	shell = {0};
	char	cwd[SIZE_PATH];
	char	*relative_path;

	header();
	while (1)
	{
		shell.buf = readline("imane> ");
		if (shell.buf == NULL)
			quit_all(&shell);
		if (!*shell.buf)
			continue ;
		add_history(shell.buf);
		shell.buf = addspaces(shell.buf);
		if (parsing(shell.buf))
			continue ;
		ft_putstr("ok parsing!\n");//oust
		// here_doc ---
		shell.buf = expand(shell.buf, info->env);
		shell.nbcmd = 0;
		
		char ** tab = ft_split_pipe(shell.buf, &shell.nbcmd);
		for (int i =0; tab[i]; i++)//oust
			printf("[%i]%s\n", i,tab[i]);//oust
		printf("nbcmd = %i\n", shell.nbcmd);//oust
		ft_pipe(&shell, tab, info->env);
		// exec
			// if nbcmd == 1
					//token(shell.buf)// appeler CREATE_CMD pour recup la commande 
					// if cmd == BUILTIN
						// redirection fichiers exec de redir avec builtind
						// retirer quotes ' et "
						// exec builtin
						// return ;
			// free(t_cmd);
			// else deux+ commandes pipex FAIT
				// fork FAIT
					// child FAIT
						// createcmd LN A FAIT -
						// redirection NAEL builtin 
						// retirer quotes JSP char *str = noquote(char *str)
						// builtin || execve si pas builint genre ls -

		// ft_print_line(shell.buf);
	}
}


// cat | ls
// echo | ls
// echo 
// ls

// if nbcmd == 1
	// appeler CREATE_CMD
	// if cmd == BUILTIN
		// redirection fichiers
		// retirer quotes
		// exec builtin
		// return to main
	// else
		// free
// fork
	// child
		// createcmd FAIT
		// redirection NAEL
		// retirer quotes JSP char *str = noquote(char *str)
		// builtin || execve

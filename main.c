/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:54:09 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/27 10:45:25 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		return_value = 0; //A renommer + init avec maccro .h

void	free_lex(char **lex)
{
	int	i;

	i = 0;
	if (lex == NULL)
		return ;
	while (lex[i] != NULL)
	{
		free(lex[i]);
		i++;
	}
	free(lex);
}

int	count_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

char	**get_env(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (count_line(envp) + 1));
	if (res == NULL)
	{
		perror("Malloc error"); //plutot perror ?
		exit(-1);
		// DEF dans le.h
	}
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]); //modification ??
		if (res[i] == NULL)
		{
			free_lex(res);          //a voir plus tard (free strlen du lexer)
			perror("Malloc error"); //plutot perror ?
			exit(-1);
			// DEF dans le.h
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	quit_all(t_shell *sh)
{
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	exit(return_value);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	prompt();
}

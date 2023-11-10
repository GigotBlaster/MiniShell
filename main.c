/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenibart <lenibart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:54:09 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/10/27 16:55:40 by lenibart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int g_ret_val = 0; A renommer + init avec maccro .h

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
		exit(-1);               DEF dans le .h
	}
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]); //modification ??
		if (res[i] == NULL)
		{
			free_lex(res);          //a voir plus tard (free strlen du lexer)
			perror("Malloc error"); //plutot perror ?
			exit(-1);               DEF dans le .h
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	signal_handler_prompt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_ret_val = 130;
	}
	if (signum == SIGQUIT)
	{
		printf("\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		i;

	signal(SIGINT, signal_handler_prompt);
	signal(SIGQUIT, signal_handler_prompt);
	signal(SIGTSTP, SIG_IGN);
	(void)ac;
	(void)av;
	i = 0;
	shell.envp = get_env(envp);
	while (1)
	{
		shell.prompt = readline("\1\033[0;32m\2minishell $> \1\033[0;m\2"); // the final newline removed
		if (shell.prompt == NULL)
		{}//free le prompt puisque que malloc par readline
		if ()
		{
			add_history(shell.prompt);
			lexer(&shell);
			parsing(&shell);
			exec(&shell);
		}
	}
	(void)shell;
	return(0);
}

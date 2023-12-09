/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:56:28 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 16:16:39 by npetitpi         ###   ########.fr       */
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

char	**ft_split_pipe(char *str, int *wc) // remplacer par split a l'appel ??
{
	int		i;
	int		j;
	int		k;
	char	**out;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '|'))
			i++;
		if (str[i])
			(*wc)++;
		while (str[i] && (str[i] != '|'))
			i++;
	}
	out = (char **)ft_calloc(sizeof(char *), ((*wc) + 1));
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

void	sig_handler_command(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		g_return_value = 130;
	}
	if (signum == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		g_return_value = 131;
	}
}

void	sig_handler_prompt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_return_value = 130;
	}
	if (signum == SIGQUIT)
	{
		printf("\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	prompt(t_info	*info)
{
	static t_pipex	shell = {0};
	char			**tab;	
	bool			first_time;

	first_time = true;
	signal(SIGINT, sig_handler_prompt);
	signal(SIGQUIT, sig_handler_prompt);
	signal(SIGTSTP, SIG_IGN);
	header();
	shell.env = info->pipex_env;
	while (1)
	{
		shell.buf = readline("MiniShell> ");
		if (shell.buf == NULL)
			quit_all(&shell);
		if (!*shell.buf)
			continue ;
		add_history(shell.buf);
		shell.buf = addspaces(shell.buf);
		if (parsing(shell.buf))
			continue ;
		// here_doc ---
		shell.buf = expand(shell.buf, shell.env);
		shell.nbcmd = 0;
		tab = ft_split_pipe(shell.buf, &shell.nbcmd);
		remspacetab(tab);
		ft_pipe(&shell, tab, shell.env, first_time);
		//maybe probleme to free
		// info->pipex_env = shell.env;
		first_time = false;
	}
}

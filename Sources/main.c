/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:54:09 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/09 20:50:33 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return_value;

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
	while (envp && envp[i] != NULL)
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
		perror("Malloc error");
		exit(-1);
	}
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]);
		if (res[i] == NULL)
		{
			free_lex(res);
			perror("Malloc error");
			exit(-1);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	quit_all(t_pipex *sh)
{
	(void)sh;
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	free_tab2(sh->env);
	exit(g_return_value);
}

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	(void)ac;
	(void)av;
	info.pipex_env = get_env(envp);
	prompt(&info);
}

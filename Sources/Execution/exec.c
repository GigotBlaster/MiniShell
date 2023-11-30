/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:04:12 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 16:23:20 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == charset))
			i++;
		if (str[i] && !(str[i] == charset))
		{
			count++;
			while (str[i] && !(str[i] == charset))
				i++;
		}
	}
	return (count);
}

static void	free_tab_exec(char ***s, int i)
{
	while (i-- > 0)
		free((*s)[i]);
	free(*s);
	*s = NULL;
}

char	*ft_strncpy2(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest [i] = '\0';
		i++;
	}
	return (dest);
}

static void	fill_words(char **split, const char *str, char charset, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < words)
	{
		while (str[j] && str[j] == charset)
			j++;
		k = 0;
		while (str[j + k] && !(str[j + k] == charset)) // pas charset, soit ' ' || '\t'
			k++;
		split[i] = ft_calloc((k + 1), sizeof(char));
		if (!split[i])
			return (free_tab_exec(&split, i));
		ft_strncpy2(split[i], &str[j], k);
		j += k;
		i++;
	}
	split[i] = 0;
}

char	**ft_splitexec(const char *str, char charset)
{
	char	**split;
	int		words_c;

	if (str == NULL)
		return (NULL);
	words_c = (count_words(str, charset));
	split = ft_calloc((words_c + 1), sizeof(char *));
	if (split == NULL)
		return (NULL);
	fill_words(split, str, charset, words_c);
	return (split);
} 
////////////////////////////////////////////////////////////

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
	free(cmd->redirections);
	free_tab2(cmd->fichiers);
	free_tab2(cmd->arguments);
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
	input = ft_splitexec(str, ' ');
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
	i = 0;
	r = 0;
	a = 0;
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

// void print_cmd(t_cmd *cmd) 
// {
// 	if (cmd->command)
// 		fprintf(stderr, "CMD: [%s]\n", cmd->command);
// 	if (cmd->arguments[0])
// 	{
// 		fprintf(stderr, "ARG: ");
// 		for (int i = 0; cmd->arguments[i]; i++) 
// 			fprintf(stderr, "[%s]", cmd->arguments[i]);
// 		fprintf(stderr, "\n");
// 	}
// 	for (int i = 0; cmd->fichiers[i]; i++)
//         fprintf(stderr, "[%i]:%s\n", cmd->redirections[i], cmd->fichiers[i]);
// }

// void	init_loop(t_data *data, char *input)
// {
// 	data_>prev_pipe = -1;
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	t_cmd *cmd;
// 	while (1)
// 	{
// 		char *str = readline("> ");
// 		if (!str)
// 			exit(1);
// 		if (!*str)
// 			continue ;
// 		add_history(str);
// 		cmd = token(str);
// 		print_cmd(cmd);
// 		free_cmd_ln(cmd);
// 	}
// 	cmd = token(av[1]);
// 	print_cmd(cmd);
// 	return(0);
// }

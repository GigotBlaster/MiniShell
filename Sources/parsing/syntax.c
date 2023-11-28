/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:11:22 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/28 19:49:26 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DQ '\"'
#define SQ '\''

int	quote_error(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == DQ || str[i] == SQ)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] != c)
				return (ft_putstr_fd("error quote\n", 2), 1);
		}
		i++;
	}
	return (0);
}

/* char *no_spaces(char *str)
{
	char *no_s;
	int i = 0;

	
	while (str[i])
	{
		
	}
} */

int 	get_tab_size(char **tab)
{
	int i;

	if (!tab)
		return (-1);
	i = 0;
	while(tab[i])
		i++;
	return (i);
}

int 	check_last(char *str)
{
	char c;
	int i;
	size_t len;
	
	len = ft_strlen(str);
	c = str[len - 1];
	if (c != '|' && c == '<' && c != '>') // le dernier caractere n est ni un | ni un < ni un > => pas d erreur syntaxe
		return (1); // syntaxe est bonne
	i = 0;
	while(str[i])
	{
		if (len == 1)
		{
			if (str[i] == '<' || str[i] == '>')
				return (ft_putstr_fd("Error syntax near unexpected token `newline'\n", 2), 1);
			else if (str[i] == '|')
				return (ft_putstr_fd("Error syntax near unexpected token `|'\n", 2), 2);
		}
		else if (len == 2)
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '<' && str[i + 1] == '>') || (str[i] == '>' && str[i + 1] == '>'))
				return (ft_putstr_fd("Error syntax near unexpected token `newline'\n", 2), 3);
			else if (str[i] == '>' && str[i + 1] == '<')
				return (ft_putstr_fd("Error syntax near unexpected token `<'\n", 2), 4);
			else if (str[i] == '<' && str[i + 1] == '|')
				return (ft_putstr_fd("Error syntax near unexpected token `|'\n", 2), 5);
		}
		i++;
	}
	return(0);
}

int	syntax_error(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[0][0] == '|')
			return(ft_putstr_fd("error pipe\n", 2), 2);
		if ((tab[i + 1] && tab[i + 1][0]) && (tab[i][0] == '|' && tab[i + 1][0] == '|'))
			return(ft_putstr_fd("error pipe\n", 2), 2);
		if (tab[i + 1])
		{
			if (is_a_redirection(tab[i]) && (is_a_redirection(tab[i + 1]) || tab[i + 1][0] == '|')) 
				return(ft_putstr_fd("syntax error bg\n", 2), 2);
		}
		i++;
	}
	int retour = check_last(tab[i - 1]);
	return (retour);
}

int	parsing(char *input)
{
	if (quote_error(input))
		return (1);
	if (syntax_error(ft_split(input, " \t")))
		return (1);
	return (0);
}

// {ls}{>}{sda}{|}{<}{sda}{|} // faux
// {ls}{>}{sda}{|}{<}{sda} // vrai

// input tu le split
// if (tab[0] == |)
//     error
// if (tab[dernier] == | > >> < <<)
//     error
// if (tab[i] == > >> < << && tab[i + 1] == > >> < << |)
//     error
// if (tab[i] == | && tab[i + 1] == |)
//     error

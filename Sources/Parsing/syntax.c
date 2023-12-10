/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:11:22 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/09 16:36:37 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DQ '\"'
#define SQ '\''

int	quote_error(char *str)
{
	int			i;
	char		c;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == DQ || str[i] == SQ)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] != c)
				return (ft_putstr_fd("syntax error near unexpected token `", 2),
					write(2, &c, 1), ft_putstr_fd("'\n", 2), 1);
		}
		i++;
	}
	return (0);
}

int	check_last(char *str)
{
	char	c;
	int		i;
	size_t	len;

	len = ft_strlen(str);
	c = str[len - 1];
	if (c != '|' && c == '<' && c != '>') // le dernier caractere n est ni un | ni un < ni un > => pas d erreur syntaxe
		return (1);// syntaxe est bonne
	i = 0;
	while (str[i])
	{
		if (len == 1)
		{
			if (str[i] == '<' || str[i] == '>')
				return (ft_putstr_fd \
				("syntax error near unexpected token `newline'\n", 2), 1);
			else if (str[i] == '|')
				return (ft_putstr_fd \
				("syntax error near unexpected token `|'\n", 2), 2);
		}
		else if (len == 2)
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '<' && \
			str[i + 1] == '>') || (str[i] == '>' && str[i + 1] == '>'))
				return (ft_putstr_fd \
				("syntax error near unexpected token `newline'\n", 2), 3);
			else if (str[i] == '>' && str[i + 1] == '<')
				return (ft_putstr_fd \
				("syntax error near unexpected token `<'\n", 2), 4);
			else if (str[i] == '<' && str[i + 1] == '|')
				return (ft_putstr_fd \
				("syntax error near unexpected token `|'\n", 2), 5);
		}
		i++;
	}
	return (0);
}

int only_spaces(char *input)
{
       int i;

       i = 0;
       while(input[i] == '\t' || input[i] == ' ')
               i++;
       if(!input[i])
               return(1);
       return(0);
}


int	syntax_error(char **tab)
{
	int	i;
	int	retour;

	i = 0;
	if (tab == NULL)
		return (ft_putstr_fd("memory error in token\n", 2), 2);
	while (tab && tab[i])
	{
		if (tab[0][0] == '|')
		{
			free_tab2(tab);
			return (ft_putstr_fd \
			("syntax error near unexpected token `|'\n", 2), 2);
		}
		if ((tab[i + 1] && tab[i + 1][0]) && \
		(tab[i][0] == '|' && tab[i + 1][0] == '|'))
		{
			free_tab2(tab);
			return (ft_putstr_fd \
			("syntax error near unexpected token `|'\n", 2), 2);
		}
		if (tab[i + 1])
		{
			if (is_a_redirection(tab[i]) && (is_a_redirection(tab[i + 1]) || \
			tab[i + 1][0] == '|'))
			{
				free_tab2(tab);
				return (ft_putstr_fd("syntax error near unexpected token `", 2),
					ft_putstr_fd(tab[i], 2), ft_putstr_fd("'\n", 2), 2);
			}
		}
		i++;
	}
	retour = check_last(tab[i - 1]);
	free_tab2(tab);
	return (retour);
}

int	parsing(char *input)
{
	if(only_spaces(input))
		return (1);
	if (quote_error(input))
		return (1);
	if (syntax_error(ft_split(input, ' '))) //? ' ' puis split '\t'
		return (1);
	if (syntax_error(ft_split(input, '\t'))) //? ' ' puis split '\t'
		return (1);
	return (0);
}


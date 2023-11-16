/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:53:29 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/16 12:57:37 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

Token	*processPipe(const char *input, int *i)
{
	Token	*token;

	token = createToken(TOKEN_PIPE, "|");
	return (token);
}

Token	*processInputRedirect(const char *input, int *i)
{
	Token	*token;

	token = createToken(TOKEN_INPUT_REDIRECT, "<");
	return (token);
}

// Token	*processAppendRedirect()
// {
// 	token = createToken(TOKEN_APPEND_REDIRECT, ">>");
// 	return (Token);
// }

Token	*processOutputRedirect(const char *input, int *i)
{
	Token	*token;

	if (input[(*i) + 1] == '>')
	{
		token = createToken(TOKEN_APPEND_REDIRECT, ">>");
		i += 2;
	}
	else
	{
		token = createToken(TOKEN_OUTPUT_REDIRECT, ">");
		i++;
	}
	return (token);
}

Token	*processDoubleQuotes(const char *input, int *index)
{
	char	doubleQuotes[MAX_TOKEN_LENGTH];
	int		j;
	Token	*token;

	j = 0;
	(*index)++;
	while (input[*index] != '"' && input[*index] != '\0')
	{
		doubleQuotes[j++] = input[(*index)++];
	}
	if (input[*index] == '"')
	{
		doubleQuotes[j] = '\0';
		(*index)++;
		token = createToken(TOKEN_DOUBLE_QUOTES, doubleQuotes);
		return (token);
	}
	return (NULL);
}

Token	*processSingleQuotes(const char *input, int *index)
{
	char	singleQuotes[MAX_TOKEN_LENGTH];
	int		j;
	Token	*token;

	j = 0;
	(*index)++;
	while (input[*index] != '\'' && input[*index] != '\0')
	{
		singleQuotes[j++] = input[(*index)++];
	}
	if (input[*index] == '\'')
	{
		singleQuotes[j] = '\0';
		(*index)++;
		token = createToken(TOKEN_SINGLE_QUOTES, singleQuotes);
		return (token);
	}
	return (NULL);
}

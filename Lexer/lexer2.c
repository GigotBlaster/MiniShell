/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:53:29 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/27 12:24:44 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*process_pipe(const char *input, int *i)
{
	t_token	*token;

	token = create_token(TOKEN_PIPE, "|");
	return (token);
}

t_token	*process_input_redirect(const char *input, int *i)
{
	t_token	*token;

	token = create_token(TOKEN_INPUT_REDIRECT, "<");
	return (token);
}

// Token	*processAppendRedirect()
// {
// 	token = createToken(TOKEN_APPEND_REDIRECT, ">>");
// 	return (Token);
// }

t_token	*process_output_redirect(const char *input, int *i)
{
	t_token	*token;

	if (input[(*i) + 1] == '>')
	{
		token = create_token(TOKEN_APPEND_REDIRECT, ">>");
		i += 2;
	}
	else
	{
		token = create_token(TOKEN_OUTPUT_REDIRECT, ">");
		i++;
	}
	return (token);
}

t_token	*process_double_quotes(const char *input, int *index)
{
	char	double_quotes[MAX_TOKEN_LENGTH];
	int		j;
	t_token	*token;

	j = 0;
	(*index)++;
	while (input[*index] != '"' && input[*index] != '\0')
	{
		double_quotes[j++] = input[(*index)++];
	}
	if (input[*index] == '"')
	{
		double_quotes[j] = '\0';
		(*index)++;
		token = create_token(TOKEN_DOUBLE_QUOTES, double_quotes);
		return (token);
	}
	return (NULL);
}

t_token	*process_single_quotes(const char *input, int *index)
{
	char	single_quotes[MAX_TOKEN_LENGTH];
	int		j;
	t_token	*token;

	j = 0;
	(*index)++;
	while (input[*index] != '\'' && input[*index] != '\0')
	{
		single_quotes[j++] = input[(*index)++];
	}
	if (input[*index] == '\'')
	{
		single_quotes[j] = '\0';
		(*index)++;
		token = create_token(TOKEN_SINGLE_QUOTES, single_quotes);
		return (token);
	}
	return (NULL);
}

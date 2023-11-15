/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:32:23 by lenibart          #+#    #+#             */
/*   Updated: 2023/11/15 14:08:19 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

Token	*createToken(TokenType type, const char *value)
{
	Token	*token;

	token = (Token *)malloc(sizeof(Token));
	token->type = type;
	ft_strlcpy(token->value, value, MAX_TOKEN_LENGTH);
	token->next = NULL;
	return (token);
}

void	freeTokens(Token *tokens)
{
	Token	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
}

Token	*processWord(const char *input, int *index)
{
	int			j;
	char		word[MAX_TOKEN_LENGTH];
	TokenType	type;
	Token		*token;

	j = 0;
	while (ft_isalnum(input[*index]) || input[*index] == '$')
	{
		j++;
		(*index)++;
	}
	if (j > 0)
	{
		ft_strlcpy(word, input + (*index) - j, j + 1);
		word[j] = '\0';
		if (word[0] == '$')
		{
			type = TOKEN_ENV_VARIABLE;
		}
		else
		{
			type = TOKEN_WORD;
		}
		token = createToken(type, word);
		return (token);
	}
	return (NULL);
}

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

Token	*lexer(const char *input)
{
	Token	*tokens;
	Token	*current;
	int		i;

	tokens = NULL;
	current = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		while (input[i] == ' ' || input[i] == '\t')
		{
			i++;
		}
		if (ft_isalpha(input[i]) || input[i] == '$')
		{
			current = processWord(input, &i);
			if (tokens == NULL)
			{
				tokens = current;
			}
		}
		else if (input[i] == '|')
		{
			current = processPipe(input, &i);
		}
		else if (input[i] == '<')
		{
			current = processInputRedirect(input, &i);
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			current = processOutputRedirect(input, &i);
		}
		// else if (input[i] == '>')
		// {
		// 	current = processOutputRedirect(input);
		// }
		else if (input[i] == '"')
		{
			current = processDoubleQuotes(input, &i);
		}
		else if (input[i] == '\'')
		{
			current = processSingleQuotes(input, &i);
		}
	}
	return (tokens);
}

void	ft_print_line(const char *input)
{
	Token	*tokens;
	Token	*current;

	tokens = lexer(input);
	current = tokens;
	while (current != NULL)
	{
		printf("Token type: %d, value: %s\n", current->type, current->value);
		current = current->next;
	}
	freeTokens(tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:32:23 by lenibart          #+#    #+#             */
/*   Updated: 2023/11/16 12:57:19 by ibouhssi         ###   ########.fr       */
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
			type = TOKEN_ENV_VARIABLE;
		else
			type = TOKEN_WORD;
		token = createToken(type, word);
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
			i++;
		if (ft_isalpha(input[i]) || input[i] == '$')
		{
			current = processWord(input, &i);
			if (tokens == NULL)
				tokens = current;
		}
		else if (input[i] == '|')
			current = processPipe(input, &i);
		else if (input[i] == '<')
			current = processInputRedirect(input, &i);
		else if (input[i] == '>' && input[i + 1] == '>')
			current = processOutputRedirect(input, &i);
		else if (input[i] == '"')
			current = processDoubleQuotes(input, &i);
		else if (input[i] == '\'')
			current = processSingleQuotes(input, &i);
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

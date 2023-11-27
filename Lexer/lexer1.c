/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:32:23 by lenibart          #+#    #+#             */
/*   Updated: 2023/11/27 12:08:49 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(e_TokenType type, const char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = type;
	ft_strlcpy(token->value, value, MAX_TOKEN_LENGTH);
	token->next = NULL;
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
}

t_token	*process_word(const char *input, int *index)
{
	int			j;
	char		word[MAX_TOKEN_LENGTH];
	e_TokenType	type;
	t_token		*token;

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
		token = create_token(type, word);
		return (token);
	}
	return (NULL);
}

t_token	*lexer(const char *input)
{
	t_token	*tokens;
	t_token	*current;
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
			current = process_word(input, &i);
			if (tokens == NULL)
				tokens = current;
		}
		else if (input[i] == '|')
			current = process_pipe(input, &i);
		else if (input[i] == '<')
			current = process_input_redirect(input, &i);
		else if (input[i] == '>' && input[i + 1] == '>')
			current = process_output_redirect(input, &i);
		else if (input[i] == '"')
			current = process_double_quotes(input, &i);
		else if (input[i] == '\'')
			current = process_single_quotes(input, &i);
		frint("je suis passerpar la")
	}
	return (tokens);
}

void	ft_print_line(const char *input)
{
	t_token current;
	current = lexer(input);

	while (current != NULL)
	{
		printf("Token type: %d, value: %s\n", current->type, current->value);
		current = current->next;
	}
	free_tokens();
}

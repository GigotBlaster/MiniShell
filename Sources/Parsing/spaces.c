/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:23:14 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/30 12:48:41 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	addlength(char *input)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (!ft_strchr("<>|", input[i]))
			len++;
		else
		{
			// if (!ft_strncmp(&input[i], "<<", 2) || !ft_strncmp(&input[i], ">>", 2))
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<') )
			{
				len += 1;
				i++;
			}
			len += 3;
		}
		i++;
	}
	return (len);
}

// <Makefile ls>out-R>>out2<out -l
// < Makefile ls > out -R >> out2 < out -l

char	*addspaces(char *input)
{
	int i;
	int j;
	char *output;

	i = -1;
	j = 0;
	int len = addlength(input);
	output = malloc(len + 1);
	if (!output)
		return (free(input), NULL);
	ft_memset(output, ' ', len);
	// printf("avant [%s]\n", input);
	while (input[++i])
	{
		if (!ft_strchr("<>|", input[i]))
			output[j++] = input[i];
		else
		{
			output[++j] = input[i];
			if (!ft_strncmp(&input[i], "<<", 2) || !ft_strncmp(&input[i], ">>",
					2))
				output[++j] = input[i++];
			j += 2;
		}
	}
	output[j] = 0;
	// printf("apres [%s] %zu | %i\n", output, ft_strlen(output), len);
	free(input);
	return (output);
}

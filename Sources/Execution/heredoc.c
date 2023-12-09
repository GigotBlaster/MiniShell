/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:44:49 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 14:37:10 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(int fd, char *charset)
{
	char	*prompt;

	prompt = readline(">");
	while (prompt && ft_strcmp(prompt, charset) != 0)
	{
		write(fd, prompt, ft_strlen(prompt));
		write(fd, "\n", 1);
		prompt = readline(">");
	}
	return (1);
}

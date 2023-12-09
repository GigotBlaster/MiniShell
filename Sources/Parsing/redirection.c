/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:54:33 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/09 14:30:55 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!strcmp(str, "|"))
		return (5);
	return (0);
}

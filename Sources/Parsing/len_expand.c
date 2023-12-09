/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:54:16 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 14:49:41 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_expand(char *str, char **env)
{
	int		len;
	int		i;
	char	*var;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == SQ)
		{
			i++;
			len++;
			while (str[i] && str[i] != SQ)
			{
				i++;
				len++;
			}
			if (!str[i])
				break ;
			i++;
			len++;
		}
		if (str[i] == DQ)
		{
			i++;
			len++;
			while (str[i] && str[i] != DQ)
			{
				while (str[i] == '$')
				{
					i++;
					var = get_value(str, &i, env);
					if (var){
						len += strlen(var);
						free(var);
						}
				}
				i++;
				len++;
			}
			if (!str[i])
				break ;
			i++;
			len++;
		}
		if (!str[i])
			break ;
		else
		{
			while (str[i] == '$')
			{
				i++;
				var = get_value(str, &i, env);
				if (var){
					len += strlen(var);
					free(var);
				}
			}
		}
		if (!str[i])
			break ;
		i++;
		len++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:56:07 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/09 14:50:15 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_expand(char *str, char **env)
{
	int		len;
	int		i;
	char	*var;
	char	*dest;

	i = 0;
	len = 0;
	dest = calloc(sizeof(char), (len_expand(str, env) + 1));
	while (str[i])
	{
		if (str[i] == SQ)
		{
			dest[len] = str[i];
			i++;
			len++;
			while (str[i] && str[i] != SQ)
			{
				dest[len] = str[i];
				i++;
				len++;
			}
			if (!str[i])
				break ;
			dest[len] = str[i];
			i++;
			len++;
		}
		if (str[i] == DQ)
		{
			dest[len++] = str[i++];
			while (str[i] && str[i] != DQ)
			{
				while (str[i] == '$' && str[i + 1])
				{
					i++;
					var = get_value(str, &i, env);
					if (var)
					{
						ft_reverse(var);
						len += strlen(var);
						strcat(dest, var);
						free(var);
					}
				}
				dest[len++] = str[i++];
			}
			if (!str[i])
				break ;
			dest[len++] = str[i++];
		}
		if (!str[i])
			break ;
		else
		{
			while (str[i] == '$' && str[i + 1])
			{
				i++;
				var = get_value(str, &i, env);
				if (var)
				{
					ft_reverse(var);
					len += strlen(var);
					strcat(dest, var);
					free(var);
				}
			}
		}
		if (!str[i])
			break ;
		dest[len++] = str[i++];
	}
	dest[len] = '\0';
	ft_reverse_all(dest);
	return (dest);
}

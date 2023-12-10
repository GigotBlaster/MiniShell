/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:46:00 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/10 18:29:13 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_env(char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		i++;
		new = ft_strdup(&str[i]);
	}
	return (new);
}

char	*get_value_from_key(char *src, char **env)
{
	int	y;

	y = 0;
	while (env && env[y])
	{
		if (!ft_strncmp(src, env[y], ft_strlen(src)) && \
		env[y][ft_strlen(src)] == '=')
			return (copy_env(env[y]));
		y++;
	}
	return (NULL);
}

char	*get_value(char *str, int *index, char **env)
{
	int		i;
	char	c;
	char	*value;
	int		tmp;

	i = 0;
	if (str[*index] == '?')
        return ((*index)++, ft_itoa(g_return_value)); 
	if (ft_isdigit(str[*index]))
		return (&str[*index + 1]);
	while (ft_isalnum(str[*index + i]) || str[*index + i] == '_')
		i++;
	c = str[*index + i];
	str[*index + i] = '\0';
	value = get_value_from_key(&str[*index], env);
	tmp = ft_strlen(&str[*index]);
	str[*index + i] = c;
	*index += tmp;
	return (value);
}

int	get_key_len(char *str, int *index)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[*index]))
		return (ft_strlen(&str[*index]));
	while (ft_isalnum(str[*index + i]) || str[*index + i] == '_')
		i++;
	return (i);
}

char	*expand(char *str, char **env)
{
	char	*new; // = malloc(sizeof(char) * (len_expand(str, env)));
	new = str_expand(str, env);
	return (new);
}

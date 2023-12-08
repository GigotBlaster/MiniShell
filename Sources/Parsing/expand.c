/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:46:00 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/08 14:27:53 by ibouhssi         ###   ########.fr       */
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

int	ft_strncmp_mini(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	
	if(str2[i++] == '=')
		return(0);
	//if (i < n)
	//	return (str1[i] - str2[i]);
	return (1);
}

char	*get_value_from_key(char *src, char **env)
{
	int		y;
	y = 0;

	while(env && env[y])
	{
		if (!ft_strncmp(src, env[y], ft_strlen(src)) &&  env[y][ft_strlen(src)] == '=')
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
	if (ft_isdigit(str[*index]))
		return (&str[*index + 1]);
	while (ft_isalnum(str[*index + i]) || str[*index + i] == '_')
		i++;
	c = str[*index + i];
	str[*index + i] = '\0';
	value = get_value_from_key(&str[*index], env);
	
	// if (!value)
	// 	return (NULL);
	
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
					if (var)
						len += strlen(var);
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
				if (var)
					len += strlen(var);
			}
		}
		if (!str[i])
			break ;
		i++;
		len++;
	}
	return (len);
}

void	ft_reverse(char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == SQ || line[i] == DQ)
			line[i] = line[i] * -1;
		i++;
	}
}

void	ft_restore(char *line)
{
		int i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			line[i] = -line[i];
		i++;
	}
}
 
void	ft_reverse_all(char *line)
{
	int i;
	int context;
	
	context = 0;

	i = 0;
	while (line[i])
	{
		if (line[i] == context)
			context = 0;
		else if(!context && line[i] == DQ)
			context = DQ;
		else if (!context && line[i] == SQ)
			context = SQ;
		else if (context == SQ || context == DQ)
		{
			if (line[i] > 0)
				line[i] *= -1;
		}
		i++;

	}
}

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

char	*expand(char *str, char **env)
{
	char *new; // = malloc(sizeof(char) * (len_expand(str, env)));
	new = str_expand(str, env);
	return (new);
}

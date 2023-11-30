/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:46:00 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/30 17:15:35 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// avion = strlen(avion)
// avion$USER = strlen(avion) + strlen(USER.value);
// 'avion$USER[reed' = strlen('avion$USER[reed')
// 'avion$USERreed' = strlen('avion$USERreed')
// "avion$USER" = strlen("avion") + strlen(USER.value);
// "avion$USER/*-+-" = strlen("avion") + strlen("ibouhssi") + strlen("/*-+-");
// "avion$?owrr" = strlen("avion")
// $1hroqiwr_*()
//  ibouhssi = USER
//  ibouhssi = USER.
//  ibouhssi = USER^
//  ibouhssi = USER&
//  NULL = USER1
//  NULL = USER_
//  NULL = USER_SDA1sas
//  NULL = USERA
//  avion$USERfhfj
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
		new = strdup(&str[i]);
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
	char	c;
	char	*value;

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

char	*str_expand(char *str, char **env)
{
	int		len;
	int		i;
	char	*var;
	char	*dest;

	// char	*dest;
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
				while (str[i] == '$')
				{
					i++;
					var = get_value(str, &i, env);
					if (var)
					{
						len += strlen(var);
						strcat(dest, var);
					}
					// else
					// {
					// 	printf("in {%s}, var == NULL\n", __func__);
					// }
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
			while (str[i] == '$')
			{
				i++;
				var = get_value(str, &i, env);
				if (var)
				{
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
	return (dest);
}

char	*expand(char *str, char **env)
{
	char *new; // = malloc(sizeof(char) * (len_expand(str, env)));
	new = str_expand(str, env);
	// printf("LEN NEW = [%zu]\n", ft_strlen(new));
	printf("NEW = [%s]\n", new);
	return (str);
}

// int main(int ac, char **av, char **env)
// {
// 	char str[] = "hello";
// 	printf("%s\n", expand(str, env));
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:46:00 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/28 22:52:38 by ibouhssi         ###   ########.fr       */
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
char *copy_env(char *str)
{
    int i;
    char *new;
    i = 0;
    new = NULL;
    while(str[i] != '=')
        i++;
    if(str[i] == '=')
    {
        i++;
        new = strdup(&str[i]);
    }
    ft_printf("Value == [%s]\n", new);
    return(new);
}

char    *get_value_from_key(char *src, char **env)
{
    int y;
    char *path;
    
    path = NULL;
    y = 0;
    while(env[y])
    {
        if (ft_strncmp(src, env[y], ft_strlen(src)) == 0)
        {
            path = copy_env(env[y]);
            if (path == NULL)
                return(NULL);
        }
        y++;
    }
    return(path);
}

char	*get_value(char *str, int *index, char **env)
{
	int		i;
    char    c;
    char    *value;


	i = 0;
	if (ft_isdigit(str[*index]))
		return (&str[*index + 1]);
	while (ft_isalnum(str[*index + i]) || str[*index + i] == '_')
		i++;
    c = str[*index + i];
    str[*index + i] = '\0';
    value = get_value_from_key(&str[*index], env);
    int tmp = ft_strlen(&str[*index]);
    str[*index + i] = c;
    *index += tmp;
	return (value);
}

int	get_key_len(char *str, int *index)
{
	int		i;
    char    c;
    char    *value;


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
            break;
		i++;
		len++;
	}
    
    
    
    //printf("len == %d\n", len);
	return (len);
}

char	*expand(char *str, char **env)
{
	(void)env;
	printf("value = %s\n", str);
	printf("input = %zu\n", strlen(str));
    // char *new = malloc(sizeof(char) * (len_expand(str, env)) + 1);
    printf("output = %i\n", len_expand(str, env));
	return (str);
}
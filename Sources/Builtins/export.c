/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:36:04 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/07 15:56:12 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	var_exist_n_replace(t_cmd *cmd, char *src)
// {
// 	char **envl;
//     int     y;
//     char    **s;
    
//     envl = cmd->environnement;
//     y = 0;
    
//     s = ft_split(src, '=');
// 	while(envl && envl[y])
// 	{
// 		if (!ft_strncmp(s[0], envl[y], ft_strlen(s[0])) &&  envl[y][ft_strlen(s[0])] == '=')
//         {
//             free(envl[y]);
//             envl[y] = ft_strdup(src);
//             return true;
//         }
// 			// return (copy_env(env[y]));
// 		y++;
// 	}
// 	return (false);
// }

// int ft_export(t_cmd *cmd)
// {
// 	int		i;
// 	char	**res;
//     char    **envl;
//     char    *vari;

// 	i = 0;
//     vari = cmd->arguments[1];
//     if(!ft_strchr(vari, '='))
//         return(0);
//     if (var_exist_n_replace(cmd, vari))
//         return(0);
//     envl = cmd->environnement;
// 	res = malloc(sizeof(char *) * (count_line(envl) + 2));
// 	if (res == NULL || !vari || cmd->arguments[2])
// 	{
// 		perror("Malloc error"); //plutot perror ?
// 		exit(-1);
// 		// DEF dans le.h
// 	}
// 	while (envl[i] != NULL)
// 	{
// 		res[i] = ft_strdup(envl[i]); //modification ??
// 		if (res[i] == NULL)
// 		{
// 			free_lex(res);          //a voir plus tard (free strlen du lexer)
// 			perror("Malloc error"); //plutot perror ?
// 			exit(-1);
// 			// DEF dans le.h
// 		}
// 		i++;
// 	}
// 	res[i] = ft_strdup(vari);
//     i++;
//     res[i] = NULL;
// 	return (SUCCESS);
// }
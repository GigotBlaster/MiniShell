/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:02:12 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/07 15:12:39 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_cmd *cmd)
{
    printf("-----------MON ECHO--------------- \n");
    int i = 1;
    int no_newline = 0;

    while (cmd->arguments[i] && strcmp(cmd->arguments[i], "-n") == 0) 
    {
        no_newline++;
        i++;
    }
    while (cmd->arguments[i]) 
    {
        printf("%s", cmd->arguments[i]);
        i++;
        if (cmd->arguments[i]) 
            printf(" ");
    }
    if (!no_newline)
        printf("\n");
}
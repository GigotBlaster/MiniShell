/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:36:33 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/10 13:54:18 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result *= sign);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	ft_exit(t_cmd *cmd, t_pipex* p)
{
	printf("---------------MON EXIT -------------\n");
	if (cmd->redirection[0] != 0 || p->nbcmd > 1)
		return (1);
	printf("Exit\n");
	if (cmd->arguments[1])
	{
		if (!ft_is_digit(cmd->arguments[1]))
		{
			printf("MiniShell> exit: ");
			printf("%s", cmd->arguments[1]);
			printf(": numeric argument required\n");
			g_return_value = 2;
		}
		else if (cmd->arguments[2])
			printf("Minishell ~ exit: too many arguments\n");
		else
			g_return_value = atoi(cmd->arguments[1]);
	}
	free_all(p, cmd);
	exit (0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:54:33 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/08 13:16:24 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// readline
// check_key
// sinon join
extern int g_return_value;


void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		g_return_value = 130;
		close(0);
	}
	if (signum == SIGQUIT)
	{
		printf("\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

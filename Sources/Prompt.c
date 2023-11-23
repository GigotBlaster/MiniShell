/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:56:28 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/23 14:25:09 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	header(void)
{
	ft_putstr("\033[1;33m  __  __ _       _     _          _ _\n");
	ft_putstr(" |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
	ft_putstr(" | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
	ft_putstr(" | |  | | | | | | \\__ \\ | | |  __/ | |\n");
	ft_putstr(" |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n\n");
}

char *del_beg_path(const char *full_path) {
    const char *beg = "/mnt/nfs/homes/";
    size_t beg_len = ft_strlen(beg);

    if (ft_strncmp(full_path, beg, beg_len) == 0) 
        return ft_strdup(full_path + beg_len);
	else
        return ft_strdup(full_path);
}

void	prompt(void)
{
	t_shell	shell;

	header();
	while (1)
	{
		char	cwd[SIZE_PATH];
		getcwd(cwd, SIZE_PATH);
		char *relative_path = del_beg_path(cwd);
		ft_putstr(relative_path);
        free(relative_path);
		shell.buf = readline("\033[1;32m -Mini@Shell- \033[0;37m");
		if (shell.buf == NULL)
			quit_all(&shell);
	}
}


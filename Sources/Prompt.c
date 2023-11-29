/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:56:28 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/29 23:33:44 by ibouhssi         ###   ########.fr       */
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

// char	*del_beg_path(full_path)
// {
// 	const char	*beg;
// 	size_t		beg_len;

// 	beg = "/mnt/nfs/homes/";
// 	beg_len = ft_strlen(beg);
// 	if (ft_strncmp(full_path, beg, beg_len) == 0)
// 		return (ft_strdup(full_path + beg_len));
// 	else
// 		return (ft_strdup(full_path));
// }

void	prompt(t_info	*info)
{
	t_shell	shell;
	char	cwd[SIZE_PATH];
	char	*relative_path;

	header();
	while (1)
	{
		// shell.buf = readline("\033[1;32m -Mini@Shell- \033[0;37m");
		shell.buf = readline("imane> ");
		// printf("readline output : %s\n", shell.buf);
		if (shell.buf == NULL)
			quit_all(&shell);
		if (!*shell.buf)
			continue ;
		add_history(shell.buf);
		shell.buf = addspaces(shell.buf);
		if (parsing(shell.buf))
			continue ;
		ft_putstr("ok parsing!\n");
		// here_doc
		// expand fini
		shell.buf = expand(shell.buf, info->env);
		// exec
			// appeler CREATE_CMD
			// if nbcmd == 1 && cmd == BUILTIN
				// redirection fichiers
				// retirer quotes
				// exec builtin
			// free(t_cmd);
			// else
				// fork
					// child
						// createcmd FAIT
						// redirection NAELLE
						// retirer quotes JSP char *str = noquote(char *str)
						// builtin || execve

		// ft_print_line(shell.buf);
	}
}

// cat | ls
// echo | ls
// echo 
// ls

// if nbcmd == 1
	// appeler CREATE_CMD
	// if cmd == BUILTIN
		// redirection fichiers
		// retirer quotes
		// exec builtin
		// return to main
	// else
		// free
// fork
	// child
		// createcmd FAIT
		// redirection NAELLE
		// retirer quotes JSP char *str = noquote(char *str)
		// builtin || execve

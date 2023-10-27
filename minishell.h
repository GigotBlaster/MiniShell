/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenibart <lenibart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:46 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/10/27 13:36:25 by lenibart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

//INCLUDES
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>

//MACROS
# define SIZE_PATH 4096

typedef struct s_shell
{
	char	**envp;
}			t_shell;

// Structure pour représenter un token

typedef struct Token {
    char* value;
    struct Token* next;
} Token;


// ///////MAIN///////
void	free_lex(char **lex);
int	count_line(char **envp);
char	**get_env(char **envp);
void	signal_handler_prompt(int signum);
// int	main(int ac, char **av, char **envp);

///////UTILS///////
int	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:46 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/15 14:09:19 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//INCLUDES BIBLI GEN
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <sys/file.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

//INCLUDE BIBLI PERSO
# include "libftfull.h"
# include "structures.h"

//MACROS
# define SIZE_PATH 4096
# define NB_CMD 3

//BUILTINS//

/*cd*/
int			nb_args(char **args);
char		*search_in_env(t_list *envl, char *var);
static int	cd_home(t_list *envl);
static int	cd_old(t_list *envl);
int			ft_cd(t_info *cmd, t_list **envl);

/*echo*/
static void	print_args(char **args, int option, int i);
static int	echo_option(t_info *cmd);
int			ft_echo(t_info *cmd, t_list **envl);

/*pwd*/
void		change_stdin_stdout(t_info *cmd);
int			ft_pdw(t_info *cmd, t_list **envl);

/*env*/
int			ft_env(t_info *cmd, t_list **envl);
void		print_envl(t_list *envl, int declare);
static void	print_unquote(t_env entry);
static void	print_quote(t_env entry);
int			authorized_char(char *s);
int			export_all(char **vars, t_list **envl, int exported);
int			print_sorted(t_list *envl, t_info *cmd);
int			add_env(char *var, char *value, t_list **envl, int exported);
static int	export_one(char *var, t_list **envl, int exported);
void		ft_lstsort(t_list **begin_list, int (*cmp)());

/*unset*/
int			variable_match(t_list *envl, char *var, int cut);
void		invalid_identifier(char *str, char *func, int exported);

//UTILS//

/*errors*/
void		print_error(char *exe, char *file, int err, char *error);
int			error_msg(int error);

/*free*/
void		free_all(char *line, t_split *split);
void		free_tree(t_tree *tree);
void		free_entry(void *ventry);
static void	free_cmd(t_info *cmd);
void		close_unused_fd(t_info *cmd);
void		free_tab(char **args);

/*use*/
int			list_size(t_list *lst);

//SOURCES
void		prompt(void);
void		header(void);

//TOKEN
Token		*lexer(const char *input);
void		ft_print_line(const char *input);

//MAIN
void		free_lex(char **lex);
int			count_line(char **envp);
char		**get_env(char **envp);
void		signal_handler_prompt(int signum);
// int	main(int ac, char **av, char **envp);

typedef int	(*t_exec)(t_info *cmd, t_list **envl);

// enum	{CMD, PIPE, LEFT, RIGHT, RRIGHT, SEMIC};
// enum	{BUILTIN, EXECUTABLE, DECLARATION, EXECBIN};
// enum	{ECHO, CD, PWD, EXPORT, UNSET, ENV, EXIT};
// enum	{RESET, SPACE, QUOTE, DB_QUOTE, REDIR, OPERATOR};
enum
{
	SUCCESS = 0,
	PIPE_FAIL = 3,
	FORK_FAIL = 4,
	ALLOCATION_FAIL = 5,
	SYNTAX_QUOTES = 6,
	SYNTAX_REDIR = 7,
	AMBIGUOUS_REDIR = 8,
	TOOMANY = 24,
	ERROR = 1,
	MISUSE = 2,
	CANTEXEC = 126,
	NOTFOUND = 127,
	CSIGINT = 130
};

#endif
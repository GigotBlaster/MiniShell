/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:46 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/11/29 17:45:39 by ibouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//BIBLI GEN
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
# include <sys/file.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

//BIBLI PERSO
# include "libftfull.h"
# include "structures.h"

////// MACROS //////
# define SIZE_PATH 4096
# define NB_CMD 3
# define SQ '\''
# define DQ '\"'

////// BUILTINS //////
/*cd*/
int			nb_args(char **args);
char		*search_in_env(t_list *envl, char *var);
static int	cd_home(t_list *envl);
static int	cd_before(t_list *envl);
int			ft_cd(t_info *cmd, t_list **envl);

/*echo*/
static void	print_args(char **args, int option, int i);
static int	echo_option(t_info *cmd);
int			ft_echo(t_info *cmd, t_comm **envl);

/*env trop de fonctions*/
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

/*exit*/
static int	ft_isnum(char *str);
static void	free_exit(t_info *cmd, t_list **envl);
int			ft_exit(t_info *cmd, t_list **envl);

/*export_sort*/
static void	*copy_entry(void *entry);
static int	cmp_entry(void *data1, void *data2);
int print_sorted(t_list *envl, t_info *cmd);

/*export*/
int ft_export(t_info *cmd, t_list **envl);

/*pwd*/
void		change_stdin_stdout(t_info *cmd);
int			ft_pdw(t_info *cmd, t_list **envl);

/*unset*/
int			variable_match(t_list *envl, char *var, int cut);
void		invalid_identifier(char *str, char *func, int exported);

////// UTILS //////
/*errors*/
void		print_error(char *exe, char *file, int err, char *error);
int			error_msg(int error);
void		invalid_identifier(char *str, char *func, int exported);

/*free*/
void		free_all(char *line, t_split *split);
void		free_tree(t_tree *tree);
void		free_entry(void *ventry);
static void	free_cmd(t_info *cmd);
void		free_tab(char **args);

/*use    trop de contions*/ 
int			authorized_char(char *s);
static char	*ft_strcut(char *line, char c);
int			variable_match(t_list *envl, char *var, int cut);
void		ft_lstsort(t_list **begin_list, int (*cmp)());
void		close_unused_fd(t_info *cmd);
int			list_size(t_list *begin_list);

////// SOURCES ////
void		header(void);
char		*del_beg_path(const char *full_path);
void	    prompt(t_info	*info);

//MAIN
void		quit_all(t_shell *sh);
void		free_lex(char **lex);
int			count_line(char **envp);
char		**get_env(char **envp);
void		signal_handler_prompt(int signum);


/*    SYNTAX.C */
int	parsing(char *input);

/* SPACES.C */
char	*addspaces(char *input);

/* CREATE_CMD.C */

int	is_a_redirection(char *str);

/* EXPAND.C */

char *expand(char *str, char **env);   
#endif
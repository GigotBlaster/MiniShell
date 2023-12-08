/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:46 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/08 15:14:12 by ibouhssi         ###   ########.fr       */
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
# include "../Libft/Includes/libftfull.h"
# include "structures.h"

////// MACROS //////
# define SIZE_PATH 4096
# define NB_CMD 3
# define SQ '\''
# define DQ '\"'

////// BUILTINS //////
/*cd*/
int			nb_args(char **args);
void    ft_cd(t_pipex *pipex, t_cmd *cmd, int forked);
void	copy_new_var(char *new, char *name, char *value);
void	cd_replace_env_var(t_pipex *pipex, char *name, char *value);
void	cd_error(t_pipex *pipex, char *dest, int forked, int type);
void	cd_add_env_var(t_pipex *pipex, char *name, char *value);

/*echo*/
void        ft_echo(t_cmd *cmd);

/*env*/
char		*search_in_env(t_list *envl, char *var);
int     ft_env(t_pipex *env, t_cmd *cmd);

/*exit*/

/*export*/
bool	var_exist_n_replace(t_cmd *cmd, char *src);

/*pwd*/
void	change_stdin_stdout(t_info *cmd);
int ft_export(t_cmd *cmd);
int 	ft_pwd(t_cmd *cmd);

/*unset*/

////// UTILS //////
/*errors*/
void		print_error(char *exe, char *file, int err, char *error);
int			error_msg(int error);
void		invalid_identifier(char *str, char *func, int exported);

/*free*/
void		free_tab(char **args);

////////////////////////s
char *noquote(char *str);
t_cmd *token(char *str);
t_cmd *token2(char **input, t_cmd *cmd);
t_cmd *token3(char **input, t_cmd *cmd);
int	check_built_in(t_cmd *cmd);

void	ft_restore(char *line);
void ft_remove_quote(char *str);

void	sig_handler_command(int signum);
void	sig_handler_prompt(int signum);

/*use    trop de contions*/ 
int			authorized_char(char *s);
int			variable_match(t_list *envl, char *var, int cut);
void		ft_lstsort(t_list **begin_list, int (*cmp)());
void		close_unused_fd(t_info *cmd);
int			list_size(t_list *begin_list);

/*pipex*/
void	ft_freeredir(t_cmd *cmd);
void	*ft_free(void **ptr);
void	dupclose(int fd, int std);
int		get_pipe(t_pipex *here, t_info *data);
int		ft_counter(char const *s, char c);
char	**ft_pipexsplit(char *s, char c);
char	**ft_pipexsplit2(const char *s, char c, char **strs, int nb_words);
char	*acces_command(char *cmd_name, char **paths);
char	*find_path(char *cmd_name, char **env);
void	ft_pipexfree(char **strs, int words_index);
void	ft_pipexfrees(char **paths);
int		ft_pipexstrncmp(char *str1, char *str2, size_t n);
size_t	ft_pipexstrlcpy(char *dst, const char *src, size_t size);
char	*ft_pipexstrjoin(char *s1, char *s2);
size_t	ft_pipexstrlen(const char *str);
int ft_pipe(t_pipex *pipex, char **av, char **env); //char **av res split tableau


////// SOURCES ////
void		header(void);
char		*del_beg_path(const char *full_path);
void	prompt(t_info	*info);

char	*remspaces(const char *str);
char **remspacetab(char **tab);

//MAIN
void		quit_all(t_pipex *sh);
void		free_lex(char **lex);
int			count_line(char **envp);
char		**get_env(char **envp);


/*    SYNTAX.C */
int	parsing(char *input);

/* SPACES.C */
char	*addspaces(char *input);

/* CREATE_CMD.C */

int	is_a_redirection(char *str);

/* EXPAND.C */

char *expand(char *str, char **env);   
char	*get_value_from_key(char *src, char **env);
#endif
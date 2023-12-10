/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:46 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/10 16:37:05 by npetitpi         ###   ########.fr       */
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

extern int g_return_value;

//////////////////////
////// BUILTINS //////
//////////////////////

/*cd*/
void	ft_cd(t_pipex *pipex, t_cmd *cmd, int forked);
void	cd_replace_env_var(t_pipex *pipex, char *name, char *value);
void	cd_error(t_pipex *pipex, char *dest, int forked, int type);
void	cd_add_env_var(t_pipex *pipex, char *name, char *value);
void	copy_new_var(char *new, char *name, char *value);

/*echo*/
void	ft_echo(t_cmd *cmd);

/*env*/
int		ft_env(t_pipex *env, t_cmd *cmd);

/*exit*/
int		ft_exit(t_cmd *cmd, t_pipex *p);

/*export*/
bool	var_exist_n_replace(t_pipex *cmd, char *src);

/*pwd*/
void	change_stdin_stdout(t_info *cmd);
int		ft_pwd(t_cmd *cmd);
void	update_pwd_vars(t_pipex *pipex, char *dir);

/*unset*/
int		ft_unset(t_pipex *pipex, t_cmd *cmd);

/*export*/
int		ft_export(t_pipex *p, t_cmd *cmd);

//////////////////////
////// EXECUTION//////
//////////////////////

/*create_command*/
t_cmd	*token(char *str);
t_cmd	*token2(char **input, t_cmd *cmd);
t_cmd	*token3(char **input, t_cmd *cmd);

/*file*/
void	file(t_info *data, t_cmd *cmd, int a);

/*heredoc*/
int		ft_heredoc(int fd, char *charset);

/*process*/
void	child_process(t_pipex *pipex, char *arg, int i);
void	parent_process(t_pipex *pipex);
void	process(t_pipex *pipex);

/*prompt*/
void	header(void);
void	prompt(t_info	*info);

///////////////////
//////PARSING//////
///////////////////

/*check_builtin*/
int		check_built_in_baby(t_pipex *p, char *str);
int		check_built_in_dad(t_pipex *p, char *str);

/*expand*/
char	*get_value(char *str, int *index, char **env);
char	*get_value_from_key(char *src, char **env);
char	*expand(char *str, char **env);

/*len_expand*/
int		len_expand(char *str, char **env);

/*redirection*/
int		is_a_redirection(char *str);

/*reverse*/
void	ft_reverse(char *line);
void	ft_reverse_all(char *line);
void	ft_restore(char *line);

/*spaces*/
char	*addspaces(char *input);
char	*remspaces(char *str);
char	**remspacetab(char **tab);

/*str_expand*/
char	*str_expand(char *str, char **env);

/*syntax*/
int		parsing(char *input);

///////////////////
////// UTILS //////
///////////////////
void	print_env(char **e); // ??

/*error*/
void	error_fd(t_info *data, t_cmd *cmd, int i);

/*free*/
void	free_tab(char **args);
void	free_tab2(char **tab);
void	free_cmd(t_cmd *cmd);
void	*ft_free(void **ptr);
void	ft_freeredir(t_cmd *cmd);
void    free_all(t_pipex *pipex, t_cmd *cmd);

char	*noquote(char *str);
int		check_built_in(t_cmd *cmd);

void	ft_remove_quote(char *str);

void	sig_handler_command(int signum);
void	sig_handler_prompt(int signum);

/*use    trop de contions*/
char	*noquote(char *str);
void	ft_remove_quote(char *str);
void	dupclose(int fd, int std);

/*pipex*/
char	*find_path(char *cmd_name, char **env);
char	*acces_command(char *cmd_name, char **paths);
int		get_pipe(t_pipex *here, t_info *data);
int		ft_pipe(t_pipex *pipex, char **av, char **env, bool f);

/*u_pipex*/
int		ft_counter(char const *s, char c);
size_t	ft_pipexstrlcpy(char *dst, const char *src, size_t size);
size_t	ft_pipexstrlen(const char *str);
void	ft_pipexfree(char **strs, int words_index);
void	ft_pipexfrees(char **paths);

/*u_pipex2*/
char	*ft_pipexstrjoin(char *s1, char *s2);
int		ft_pipexstrncmp(char *str1, char *str2, size_t n);
char	**ft_pipexsplit(char *s, char c);
char	**ft_pipexsplit2(const char *s, char c, char **strs, int nb_words);

//MAIN
void	quit_all(t_pipex *sh);
void	free_lex(char **lex);
int		count_line(char **envp);
char	**get_env(char **envp);


void ft_hold_var(int action, t_pipex *pip, char **tab);

#endif
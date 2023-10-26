#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		ft_counter(char const *s, char c);
void	ft_free(char **strs, int words_index);
char	**ft_split_pipex(char *s, char c);
char	**ft_split2_pipex(const char *s, char c, char **strs, int nb_words);
size_t	ft_strlcpy_pipex(char *dst, const char *src, size_t size);
char	*acces_command(char *cmd_name, char **paths);
char	*find_path(char *cmd_name, char **env);
int		initiate_child_process(char **av, int i, int *pipe_fd, char **env);
int		main(int ac, char **av, char **env);
void	ft_frees(char **paths);
void	ft_error(void);
void	fail_execve(char **arg);
void	first_cmd(char **env, char *infile, char **arg, int *pipe_fd);
void	second_cmd(char **env, char *outfile, char **arg, int *pipe_fd);
char	*ft_strchr_pipex(const char *str, int c);
int		ft_strncmp_pipex(char *str1, char *str2, size_t n);
char	*ft_strjoin_pipex(char *s1, char *s2);
size_t	ft_strlen_pipex(const char *str);
void	close_all(int fd, int pipefd[2]);

#endif
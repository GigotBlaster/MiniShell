/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:12:56 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/30 17:23:45 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "libftstructures.h"
# include <stdarg.h>

//MACRO
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_TOKEN_LENGTH 100

typedef struct s_comm
{
	char			*file;
	char			**argv;
}					t_comm;

typedef struct s_shell
{
}					t_shell;

typedef struct s_split
{
	char			*str;
}					t_split;

typedef struct s_info
{
	char			*line;
	void			*root;
	int				output;
	int				input;
	int				*spaces_tmp;
	int				number;
	char			**argv;
	int				offset;
	int				is_subprocess;
	char			**args_tmp;
	char			*seps_tmp;
	int				*spaces;
	char			**args;
	char			*seps;
	char			**env;
	t_split			*split;
}					t_info;

typedef struct s_tree
{
	t_info			*info;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				exported;
}					t_env;

typedef struct s_pipex {
	char			*buf;
	int pipe_fd[2];
	char **env;
	int prev;
	int nbcmd;
	char **cmds;
	int  *pid;
}	t_pipex;

enum
{
	SUCCESS = 0,
	ERROR = 1,
	MISUSE = 2,
	FORK_FAIL = 4,
	ALLOCATION_FAIL = 5,
};

typedef struct s_cmd
{
    int     *redirections;
    char    **fichiers;
    char    **arguments;
    char    *command;
}           t_cmd;
#endif
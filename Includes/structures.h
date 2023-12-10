/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:12:56 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 20:12:15 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <stdarg.h>

//MACRO
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_TOKEN_LENGTH 100

typedef struct s_redir
{
	int				type;
	char			*inside;
	struct s_redir	*next;
}				t_redir;

typedef struct s_pipex
{
	char	*buf;
	char	*stop;
	int		pipe_fd[2];
	char	**env;
	int		prev;
	int		nbcmd;
	char	**cmds;
	int		*pid;
}				t_pipex;

typedef struct s_info
{
	char			*line;
	int				output;
	int				input;
	int				fd[2];
	char			*file;
	t_pipex			*here;
	char			**pipex_env;
}				t_info;

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
	int		*redirection;
	char	**fichiers;
	char	*flag;
	char	**arguments;
	t_redir	*redir;
	char	*command;
	char	**environnement;
}				t_cmd;
#endif
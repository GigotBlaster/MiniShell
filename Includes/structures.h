/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:12:56 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/27 14:55:01 by npetitpi         ###   ########.fr       */
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
	char			*buf;
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


typedef enum token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INPUT_REDIRECT,
	TOKEN_OUTPUT_REDIRECT,
	TOKEN_APPEND_REDIRECT,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_SINGLE_QUOTES,
	TOKEN_ENV_VARIABLE
}					e_TokenType;

typedef struct Token
{
	char			value[MAX_TOKEN_LENGTH];
	e_TokenType		type;
	struct Token	*next;
}					t_token;

#endif
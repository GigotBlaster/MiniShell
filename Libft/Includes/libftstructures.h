/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftstructures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:11:01 by npetitpi          #+#    #+#             */
/*   Updated: 2023/12/08 19:51:45 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSTRUCTURES_H
# define LIBFTSTRUCTURES_H
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4095
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_buffer
{
	int				size;
	char			content[BUFFER_SIZE + 1];
}					t_buffer;

typedef struct s_print
{
	int				align;
	int				zero;
	int				field;
	int				precision;
	int				type;
	int				fd;
}					t_print;

typedef int	(*t_func)(t_print, va_list);

#endif
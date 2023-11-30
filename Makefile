# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 11:57:52 by ibouhssi          #+#    #+#              #
#    Updated: 2023/11/30 19:11:51 by npetitpi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME          = ./minishell


NAME			=	minishell

LIBFT			=	libft.a

DIR_SRCS		=	Sources

DIR_OBJS		=	Objets

CFLAGS			= -Wall -Werror -Wextra -g3
CC				= cc
RM      	    = rm -rf

SRCS_NAMES		= Builtins/unset.c \
				  Builtins/export_sort.c \
				  Builtins/exit.c.c \
				  Builtins/cd.c \
				  Builtins/env.c \
				  Builtins/echo.c \
				  Builtins/export.c \
				  Builtins/pwd.c \
				  Parsing/spaces.c \
				  Parsing/expand.c \
				  Parsing/syntax.c \
				  main.c \
				  Prompt.c \
				  Execution/exec.c \
				  Utils/u2pipex.c \
				  Utils/upipex.c \
				  Utils/errors.c \
				  Utils/use.c \
				  Utils/pipex.c \
				  Utils/free.c \


OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-IIncludes -ILibft/Includes

LIB				=	-lreadline -lm -LLibft -lft


all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS) 
	@make -C Libft > /dev/null
	@$(CC) -g3 ${INC} $(OBJS) $(LIB) -o $(NAME) > /dev/null
	@printf "\033[32mMiniShell compiled\033[0m$(SPACES)"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	@printf "[..] $(NAME) compiling... $*.c\r" && $(CC) -g3 $(CDFLAGS) $(INC) -c $< -o $@ && printf "$(_CLEAR)"

$(DIR_OBJS):
	@mkdir -p $(DIR_OBJS) > /dev/null
	@mkdir -p $(DIR_OBJS)/Builtins > /dev/null
	@mkdir -p $(DIR_OBJS)/Execution > /dev/null
	@mkdir -p $(DIR_OBJS)/Parsing > /dev/null
	@mkdir -p $(DIR_OBJS)/Utils > /dev/null

clean:
	@make clean -C Libft > /dev/null
	@rm -rf ${DIR_OBJS}

fclean: clean
	@make fclean -C Libft > /dev/null
	@rm -rf ${LIBFT}
	@rm -rf ${NAME}

leaks: ${NAME}
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

leask: $(NAME)
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell


env: $(NAME)
	env -i ./minishell

stop:
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop
# .SILENT:
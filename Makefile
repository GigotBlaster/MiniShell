# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 23:12:33 by ibouhssi          #+#    #+#              #
#    Updated: 2023/12/09 13:29:03 by npetitpi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

LIBFT			=	libft.a

DIR_SRCS		=	Sources

DIR_OBJS		=	Objets

CFLAGS			= -Wall -Werror -Wextra -g3
CC				= cc
RM      	    = rm -rf

SRCS_NAMES		= Builtins/unset.c \
				  Builtins/exit.c \
				  Builtins/cd.c \
				  Builtins/env.c \
				  Builtins/cd_utils.c\
				  Builtins/echo.c \
				  Builtins/export.c \
				  Builtins/pwd.c \
				  Parsing/spaces.c \
				  Parsing/check_builtin.c \
				  Parsing/expand.c \
				  Parsing/len_expand.c \
				  Parsing/redirection.c \
				  Parsing/reverse.c \
				  Parsing/str_expand.c \
				  Parsing/syntax.c \
				  main.c \
				  Execution/Prompt.c \
				  Execution/create_command.c \
				  Execution/file.c \
				  Execution/process.c \
				  Execution/heredoc.c \
				  Utils/upipex2.c\
				  Utils/upipex.c \
				  Utils/errors.c \
				  Utils/use.c \
				  Utils/pipex.c \
				  Utils/free.c \


OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-IIncludes -ILibft/Include

LIB				=	-lreadline -lm -LLibft -lft


all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS) 
	@make -C Libft > /dev/null
	@$(CC) -g3 ${INC} $(OBJS) $(LIB) -o $(NAME) > /dev/null
	@printf "\033[32mMiniShell compiled\033[0m$(SPACES)"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	@printf "[..] $(NAME) compiling... $*.c\r" && $(CC) -g3 $(CFLAGS) $(INC) -c $< -o $@ && printf "$(_CLEAR)"

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


env: $(NAME)
	env -i ./minishell

stop:
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop
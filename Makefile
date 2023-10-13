# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouhssi <ibouhssi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 11:57:52 by ibouhssi          #+#    #+#              #
#    Updated: 2023/10/13 16:10:40 by ibouhssi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC            = clang -Wall -Wextra -Werror -pthread -g3 #-fsanitize=thread 
RM            = rm -rf
NAME        = ./minishell
NAME_SHORT    = minishell

#INCS_DIR    = Includes
#MAIN_INC    = -I$(INCS_DIR)
#INCS        = $(shell find $(INCS_DIR) -type f -name "*.h")

#SRCS_DIR     = Sources
SRCS        = $(shell find $ -type f -name "*.c")

OBJS        = $(SRCS:.c=.o)

_COLOR        = \033[32m
_BOLDCOLOR    = \033[32;1m
_RESET        = \033[0m
_CLEAR        = \033[0K\r\c
_OK            = [\033[32mOK\033[0m]

%.o            : %.c $(INCS_DIR)/minishell.h
			@echo "[..] $(NAME_SHORT)... compiling $*.c\r\c"
			@$(CC) $(MAIN_INC) -c $< -o $@
			@echo "$(_CLEAR)"

all            : $(NAME)

$(NAME)        : $(OBJS) 
			@$(CC) $(OBJS) -o $(NAME)
			@echo "$(_OK) $(NAME_SHORT) compiled"

clean        :
			@$(RM) $(OBJS)

fclean        : clean
			@$(RM) $(NAME)

re            : fclean all

norme        :
			@norminette $(SRCS) $(INCS)

.PHONY        : all clean fclean re norme
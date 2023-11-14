# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 11:57:52 by ibouhssi          #+#    #+#              #
#    Updated: 2023/11/07 13:54:51 by npetitpi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Werror -Wextra -g3
CC		= cc
RM            = rm -rf
NAME          = ./minishell
NAME_SHORT    = minishell

INCS_DIR    = Includes
MAIN_INC    = -I$(INCS_DIR)
INCS        = $(shell find $(INCS_DIR) -type f -name "*.h")

SRCS_DIR     = Sources
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
			@$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)
			@echo "$(_OK) $(NAME_SHORT) compiled"


clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(OBJS) $(NAME) 2>/dev/null

re: fclean all

.PHONY = all clean fclean re

norme        :
			@norminette $(SRCS) $(INCS)

.PHONY        : all clean fclean re norme
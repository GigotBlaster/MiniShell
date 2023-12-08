CC			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
NAME		= libft.a
LIB			= ar rcs

INCS_DIR	= ./Includes/
INCS		= $(addprefix $(INCS_DIR), libftfull.h libftstructures.h)

SRCS		= Convert/ft_atoi.c \
			  Convert/ft_itoa.c \
			  Convert/ft_max.c \
			  Convert/ft_min.c \
			  Convert/ft_tolower.c \
			  Convert/ft_toupper.c \
			  Convert/ft_utoa.c \
			  Convert/ft_utoct.c \
			  Convert/ft_utox.c \
			  Convert/ft_utoxx.c \
			  Gnl/get_next_line.c \
			  Gnl/get_next_line_utils.c \
			  List/ft_lstclear.c \
			  List/ft_lstdelone.c \
			  List/ft_lstiter.c \
			  List/ft_lstlast.c \
			  List/ft_lstnew.c \
			  List/ft_lstsize.c \
			  Memory/ft_bzero.c \
			  Memory/ft_calloc.c \
			  Memory/ft_memccpy.c \
			  Memory/ft_memchr.c \
			  Memory/ft_memcmp.c \
			  Memory/ft_memcpy.c \
			  Memory/ft_memmove.c \
			  Memory/ft_memset.c \
			  String/ft_strchr.c \
			  String/ft_strdup.c \
			  String/ft_strncpy.c \
			  String/ft_strjoin.c \
			  String/ft_strlcat.c \
			  String/ft_strlcpy.c \
			  String/ft_split.c \
			  String/ft_strlen.c \
			  String/ft_strmapi.c \
			  String/ft_strcmp.c \
			  String/ft_strncmp.c \
			  String/ft_strnstr.c \
			  String/ft_strrchr.c \
			  String/ft_strtrim.c \
			  String/ft_substr.c \
			  Type/ft_isalnum.c \
			  Type/ft_isalpha.c \
			  Type/ft_isascii.c \
			  Type/ft_isdigit.c \
			  Type/ft_isprint.c \
			  Type/ft_isspace.c \
			  Type/ft_issep.c \
			  Write/ft_putchar.c \
			  Write/ft_putchar_fd.c \
			  Write/ft_putendl.c \
			  Write/ft_putendl_fd.c \
			  Write/ft_putnbr.c \
			  Write/ft_putnbr_fd.c \
			  Write/ft_putstr.c \
			  Write/ft_putstr_fd.c

PRINT_SRCS	= $(addprefix PrintF/, ft_printf.c ft_printf_fd.c \
			Parse/errors.c \
			Parse/params.c \
			Print/print_0chr.c \
			Print/print_1str.c \
			Print/print_2ptr.c \
			Print/print_3dbl.c \
			Print/print_4int.c \
			Print/print_5uns.c \
			Print/print_6hex.c \
			Print/print_7hexx.c \
			Print/print_8pct.c \
			Print/print_9oct.c \
			Print/fun_print_str.c \
			Print/fun_print_int.c \
			Print/fun_print_int_bis.c \
			Print/print.c \
			Print/utils.c)


OBJS		= $(SRCS:.c=.o) $(PRINT_SRCS:.c=.o)

%.o			: %.c
			@$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			@$(LIB) $(NAME) $(OBJS)

clean:
			@$(RM) $(OBJS)

fclean		: clean
			@$(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean re

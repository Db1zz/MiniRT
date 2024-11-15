# Project compiler settings
CC = cc
ARCH := $(shell uname -m)
ifneq ($(ARCH),x86_64)
	CFLAGS = -arch $(ARCH) -Wall -Werror -Wextra
else
	CFLAGS = -Wall -Werror -Wextra
endif
# CFLAGS = -fsanitize=address

# Project/Binary Name
NAME = libft.a

# Project Files
SRCS =	ft_atoi.c 							\
		ft_atof.c							\
		ft_strncpy.c 						\
		ft_isdigit.c 						\
		ft_memchr.c 						\
		ft_putendl_fd.c 					\
		ft_striteri.c 						\
		ft_strncmp.c					 	\
		ft_toupper.c						\
		ft_bzero.c 							\
		ft_isprint.c 						\
		ft_memcmp.c 						\
		ft_putnbr_fd.c 						\
		ft_strjoin.c 						\
		ft_strnstr.c 						\
		ft_calloc.c 						\
		ft_itoa.c 							\
		ft_memcpy.c 						\
		ft_putstr_fd.c 						\
		ft_strlcat.c 						\
		ft_strrchr.c 						\
		ft_isalnum.c 						\
		ft_memmove.c 						\
		ft_split.c 							\
		ft_strlcpy.c 						\
		ft_strtrim.c 						\
		ft_isalpha.c 						\
		ft_memset.c 						\
		ft_strchr.c 						\
		ft_strcmp.c							\
		ft_strlen.c 						\
		ft_substr.c 						\
		ft_isascii.c 						\
		ft_putchar_fd.c 					\
		ft_strdup.c 						\
		ft_strmapi.c 						\
		ft_tolower.c 						\
		ft_lstnew.c							\
		ft_lstadd_front.c					\
		ft_lstsize.c						\
		ft_lstlast.c						\
		ft_lstadd_back.c					\
		ft_lstclear.c						\
		ft_lstdelone.c						\
		ft_lstiter.c						\
		ft_lstmap.c							\
		ft_printf/src/ft_bitwise.c 			\
		ft_printf/src/ft_converter.c 		\
		ft_printf/src/ft_display_format.c 	\
		ft_printf/src/ft_get_second.c 		\
		ft_printf/src/ft_get.c 				\
		ft_printf/src/ft_istrue.c 			\
		ft_printf/src/ft_printf.c 			\
		ft_printf/src/ft_utils.c			\
		get_next_line/get_next_line_utils.c	\
		get_next_line/get_next_line.c		\

OBJS = $(SRCS:.c=.o)

# Compile Library
all: $(NAME) 

$(NAME): $(OBJS)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning Commands
clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) a.out

re:	fclean all

# Exclude these commands from execution
.PHONY: all clean fclean re bonus
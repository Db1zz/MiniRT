# Project settings
NAME = miniRT
CC = cc
UNAME_S := $(shell uname -s)
FLAGS = -Wall -Wextra -g #-Werror
MINILIBX_TGZ_NAME = MiniLibX.tgz
MINILIBX_DIR = minilibx
MINILIBX := $(MINILIBX_DIR)/libmlx.a
LIBFT = libft/libft.a
LIBFT_DIR = libft
SRCS =	src/minirt.c					\
		src/camera.c					\
		src/color.c						\
		src/error.c						\
		src/light.c						\
		src/utils.c						\
		src/vector.c					\
		src/parser/object_parser.c		\
		src/parser/parser_utils.c		\
		src/parser/parser.c				\
		src/parser/shape_parser.c		\
		src/render/pixel.c
SRCS_DIR = src
OBJS = $(SRCS:src/%.c=objs/%.o)
OBJS_DIR = objs
INCLUDE := -I include -I libft -I libft/get_next_line -I $(MINILIBX_DIR)
ifeq ($(UNAME_S), Linux)
	LIB_URL = https://cdn.intra.42.fr/document/document/26192/minilibx-linux.tgz
	FLAGS_MINILIBX = -I/usr/include -Imlx_linux -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S), Darwin)
	LIB_URL = https://cdn.intra.42.fr/document/document/26193/minilibx_opengl.tgz
	FLAGS_MINILIBX = -framework OpenGL -framework AppKit #-Lmlx
endif

all: $(MINILIBX_DIR) $(MINILIBX) $(LIBFT) $(OBJS) $(NAME)

$(MINILIBX_DIR):
	@echo "Downloading MiniLibX for $(UNAME_S) from $(LIB_URL)"
	curl -L -o $(MINILIBX_TGZ_NAME) $(LIB_URL)
	@echo "Download completed."
	@mkdir -p $(MINILIBX_DIR)
	tar -xzf $(MINILIBX_TGZ_NAME) -C $(MINILIBX_DIR) --strip-components 1
	rm -f $(MINILIBX_TGZ_NAME)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/render
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(FLAGS_MINILIBX) $(MINILIBX) $(LIBFT) $(INCLUDE) -o $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
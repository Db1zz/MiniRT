# Project settings
NAME = miniRT
CC = cc
UNAME_S := $(shell uname -s)
FLAGS := -Wall -Wextra -O2 #-Werror
MINILIBX_DIR = minilibx
MINILIBX := $(MINILIBX_DIR)/libmlx.a
LIBFT = libft/libft.a
LIBFT_DIR = libft
SRCS =	src/minirt.c	\
		src/parser/object_parser.c	\
		src/parser/parser.c	\
		src/parser/parser_utils.c	\
		src/parser/shape_parser.c	\
		src/render/camera/camera.c	\
		src/render/camera/viewport.c	\
		src/render/ray/light_utils.c	\
		src/render/ray/light.c	\
		src/render/ray/ray_reflections.c	\
		src/render/ray/ray_utils.c	\
		src/render/ray/ray.c	\
		src/render/ray/threads.c \
		src/render/shapes/cylinder_math.c	\
		src/render/shapes/gyper_math.c	\
		src/render/shapes/plane_math.c	\
		src/render/shapes/sphere_math.c	\
		src/render/shapes/aabb.c	\
		src/render/shapes/bvh.c	\
		src/render/utilities/bvh_utils.c	\
		src/render/utilities/antialiasing.c	\
		src/render/utilities/bvh_print_tree.c	\
		src/render/utilities/color_math1.c	\
		src/render/utilities/color_math2.c	\
		src/render/utilities/color_math3.c	\
		src/render/utilities/color.c	\
		src/render/utilities/error.c	\
		src/render/utilities/interval.c	\
		src/render/utilities/math_utils.c	\
		src/render/utilities/object.c	\
		src/render/utilities/pixel.c	\
		src/render/utilities/render.c	\
		src/render/utilities/utils.c	\
		src/render/utilities/vector_math1.c	\
		src/render/utilities/vector_math2.c	\
		src/render/utilities/vector_math3.c	\
		src/render/utilities/vector_math4.c	\
		src/render/utilities/vector.c	\
		src/render/utilities/scene.c	\
		src/render/utilities/timer.c	\
		src/render/utilities/xpm_render.c	\

SRCS_DIR = src
OBJS = $(SRCS:src/%.c=objs/%.o)
OBJS_DIR = objs
INCLUDE := -I include -I libft -I libft/get_next_line -I $(MINILIBX_DIR)
ifeq ($(UNAME_S), Linux)
	LIB_URL = https://github.com/42Paris/minilibx-linux
	FLAGS_MINILIBX = -I/usr/include -Imlx_linux -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S), Darwin)
	LIB_URL = https://github.com/Db1zz/minilibx_opengl
	FLAGS_MINILIBX = -framework OpenGL -framework AppKit #-Lmlx
endif

all: $(MINILIBX_DIR) $(MINILIBX) $(LIBFT) $(OBJS) $(NAME)

$(MINILIBX_DIR):
	@echo "Downloading MiniLibX for $(UNAME_S) from $(LIB_URL)"
	@echo "Download completed."
	git clone $(LIB_URL) $(MINILIBX_DIR)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/render $(OBJS_DIR)/parser $(OBJS_DIR)/render/camera $(OBJS_DIR)/render/ray $(OBJS_DIR)/render/utilities $(OBJS_DIR)/render/shapes
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

bonus:
	$(MAKE) FLAGS="$(FLAGS) -D BONUS" all

.PHONY: all clean fclean re bonus
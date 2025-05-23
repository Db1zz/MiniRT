# Project settings
NAME = miniRT
CC = cc
UNAME_S := $(shell uname -s)
FLAGS := -Wall -Wextra -Werror -O3
MINILIBX_DIR = minilibx
MINILIBX := $(MINILIBX_DIR)/libmlx.a
LIBFT = libft/libft.a
LIBFT_DIR = libft
SRCS =	src/main.c	\
		src/minirt.c	\
		src/minirt_bonus.c	\
		src/parser/object_parser.c	\
		src/parser/parser.c	\
		src/parser/parser_utils.c	\
		src/parser/parser_utils2.c	\
		src/parser/shape_parser.c	\
		src/parser/shape_parser_bonus.c	\
		src/parser/texture_parser.c \
		src/render/render.c	\
		src/render/render_bonus.c	\
		src/render/render_workers_bonus.c	\
		src/render/render_routine_bonus.c	\
		src/render/scene.c	\
		src/render/scene_destroy.c	\
		src/render/scene_add_functions.c	\
		src/render/camera/camera.c	\
		src/render/camera/camera2.c	\
		src/render/camera/viewport.c	\
		src/render/ray/aabb_math.c	\
		src/render/ray/light_utils.c	\
		src/render/ray/light.c	\
		src/render/ray/hit_record.c	\
		src/render/ray/ray_utils.c	\
		src/render/ray/ray_shapes.c	\
		src/render/ray/ray_routine.c	\
		src/render/ray/ray_light.c	\
		src/render/ray/ray_bvh.c	\
		src/render/ray/cylinder_math.c	\
		src/render/ray/cylinder_math2.c	\
		src/render/ray/gyper_math.c	\
		src/render/ray/plane_math.c	\
		src/render/ray/sphere_math.c	\
		src/render/ray/aabb_compute.c	\
		src/render/ray/aabb.c	\
		src/render/ray/bvh.c	\
		src/render/ray/bvh_merge_sort.c	\
		src/render/ray/plane_texture.c	\
		src/render/object/object.c	\
		src/render/object/object_destroyer.c	\
		src/render/utilities/pepe_barrier.c	\
		src/render/utilities/bvh_print_tree.c	\
		src/render/utilities/bvh_utils.c \
		src/render/utilities/color_math1.c	\
		src/render/utilities/color_math2.c	\
		src/render/utilities/color.c	\
		src/render/utilities/error.c	\
		src/render/utilities/error_messages.c	\
		src/render/utilities/interval.c	\
		src/render/utilities/math_utils.c	\
		src/render/utilities/utils.c	\
		src/render/utilities/vector_math1.c	\
		src/render/utilities/vector_math2.c	\
		src/render/utilities/vector_math3.c	\
		src/render/utilities/vector.c	\
		src/render/utilities/xpm_render.c	\

SRCS_DIR = src
OBJS = $(SRCS:src/%.c=objs/%.o)
OBJS_DIR = objs
INCLUDE := -I include -I libft -I libft/get_next_line -I $(MINILIBX_DIR)
ifeq ($(UNAME_S), Linux)
	LIB_URL = https://github.com/42Paris/minilibx-linux
FLAGS_MINILIBX = -I /usr/include/X11/Xlib.h -L/usr/lib/aarch64-linux-gnu/ -L/usr/include/X11 -L/usr/lib -L/usr/include -Lminilibx -lmlx -lXext -lX11 -lm -I/usr/include -I/usr/include/X11
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
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/render $(OBJS_DIR)/parser $(OBJS_DIR)/render/camera $(OBJS_DIR)/render/ray $(OBJS_DIR)/render/utilities $(OBJS_DIR)/render/object
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
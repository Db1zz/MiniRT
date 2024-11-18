#ifndef MINIRT_H
# define MINIRT_H

# include "ft_error.h"
# include "parser.h"
# include "dependencies.h"
# include <stdlib.h>

# ifdef __APPLE__
	#  include "keu_macos.h"
# elif __linux__
	#  include "key_linux.h"
# endif

# define WIN_WIDTH 1024
# define WIN_HEIGHT 720
# define WIN_ASPECT_RATIO 1.42


void	free_2dmatrix(char **matrix);
bool	is_string_number(char *line);
size_t	get_2dmatrix_size(char **matrix);
bool	check_str_numbers(char **numbers, int expected_size);

// Converters
int		rgb_to_int(t_color *color);

// Pixel-related functions
void	draw_pixel(t_scene *scene, int x, int y, t_color *color);

#endif //	MINIRT_H

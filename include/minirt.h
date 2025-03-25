#ifndef MINIRT_H
# define MINIRT_H

# include "ft_error.h"
# include "libft.h"
# include "mlx.h"
# include "parser.h"
# include "object.h"
# include "minirt_math.h"
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# ifdef __APPLE__
#  include "key_macos.h"
# elif __linux__
#  include "key_linux.h"
# endif

# define WIN_WIDTH 1024
# define WIN_HEIGHT 720
# define ANTIALIASING_SAMPLES 2

/* Rendering functions */
void	draw_pixel(t_scene *scene, int x, int y, t_color color);
t_color	apply_antialiasing(t_color ray_color, t_scene *scene, int x, int y);
void	render(t_scene *scene);

#endif //	MINIRT_H
//fedia was herrr
#ifndef MINIRT_H
# define MINIRT_H

# include "ft_error.h"
# include "parser.h"
# include "dependencies.h"
# include <stdlib.h>
# include <math.h>

# ifdef __APPLE__
	#  include "key_macos.h"
# elif __linux__
	#  include "key_linux.h"
# endif

# define WIN_WIDTH 1024
# define WIN_HEIGHT 720
# define WIN_ASPECT_RATIO 1.42

// Rendering functions
void	draw_pixel(t_scene *scene, int x, int y, t_color color);
void	render(t_scene *scene);

#endif //	MINIRT_H

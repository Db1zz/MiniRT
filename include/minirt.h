#ifndef MINIRT_H
#define MINIRT_H

#include "mlx.h"
#include "ft_error.h"
#include "libft.h"
#include "parser.h"
#include "object.h"
#include "scene.h"
#include "minirt_math.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include "key_macos.h"
#elif __linux__
#include "key_linux.h"
#endif

/* Rendering functions */
void draw_pixel(t_scene *scene, int x, int y, t_color *color);
t_color apply_antialiasing(t_color ray_color, t_scene *scene, int x, int y);
void render(t_scene *scene);

#endif //	MINIRT_H
	   // fedia was herrr
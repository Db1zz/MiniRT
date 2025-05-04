#ifndef MINIRT_H
# define MINIRT_H

#include "mlx.h"
#include "ft_error.h"
#include "libft.h"
#include "parser.h"
#include "object.h"
#include "scene.h"
#include "minirt_math.h"
#include "render.h"

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include "key_macos.h"
#elif __linux__
#include "key_linux.h"
#endif

typedef struct s_minirt_ctx
{
	t_scene	scene;
	t_render_workers_ctx workers;
}	t_minirt_ctx;

int	minirt_routine(int argc, char **argv);

#endif //	MINIRT_H
	   // fedia was herrr
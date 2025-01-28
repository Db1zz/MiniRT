#ifndef UTILS_H
# define UTILS_H

# include "scene.h"
# include <stdlib.h>

/* Utility functions */
void	*rt_calloc(size_t count, size_t size, t_scene* scene);
void	free_2dmatrix(char **matrix);
size_t	get_2dmatrix_size(char **matrix);
double	div_c(double v1, double v2);

#endif // !UTILS_H

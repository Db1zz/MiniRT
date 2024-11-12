#ifndef PARSER_H
# define PARSER_H

#include "scene.h"
#include <stdlib.h>

#define CYLINDER_ARGS 6
#define PLANE_ARGS 5
#define SPHERE_ARGS 3

int		normalize_vector(t_vector *vector);
t_scene	*parse_input(int argc, char **argv);
int		parse_sphere(t_scene *scene, const char **line_data);
int		parse_cylinder(t_scene *scene, const char **line_data);

#endif // PARSER_H
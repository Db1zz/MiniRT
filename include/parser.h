#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "ft_error.h"
# include <stdlib.h>

# define CYLINDER_ARGS 6
# define PLANE_ARGS 5
# define SPHERE_ARGS 3

t_error	scene_parser(t_scene *scene, int scene_fd);

t_error	normalize_vector(t_vector *vector);
t_scene	*parse_input(int argc, char **argv);
t_error	parse_sphere(t_scene *scene, const char **line_data);
t_error	parse_cylinder(t_scene *scene, const char **line_data);
t_error	parse_plane(t_scene *scene, char **line_data);

t_error	parse_light(t_scene *scene, const char **line_data);
t_error	parse_ambient(t_scene *scene, const char **line_data);
t_error	parse_camera(t_scene *scene, const char **line_data);

#endif // PARSER_H
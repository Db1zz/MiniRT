#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include <stdlib.h>

# define CYLINDER_ARGS 6
# define PLANE_ARGS 5
# define SPHERE_ARGS 3

t_error parse_input(t_scene *scene, int argc, char **argv);

t_object *add_object_to_array(
	void *object, t_object_type type, t_object **arr, size_t *arr_size);

void parse_gyper(
	t_scene *scene,
	char **line_data);

void	parse_sphere(
			t_scene *scene,
			char **line_data);

void	parse_cylinder(
			t_scene *scene,
			char **line_data);

void	parse_plane(
			t_scene *scene,
			char **line_data);

void	parse_light(
			t_scene *scene,
			char **line_data);

void	parse_ambient(
			t_scene *scene,
			char **line_data);

void	parse_camera(
			t_scene *scene,
			char **line_data);

/* Utility Functions */
bool	check_str_numbers(
			char **numbers,
			int expected_size,
			t_scene *scene);

void	str_to_color(
			t_color *color,
			const char *str,
			t_scene *scene);

void	str_to_vector(
			t_vector *result,
			const char *vector_str,
			bool normalize,
			t_scene *scene);

bool	is_string_number(
			const char *line,
			t_scene *scene);

double	rt_atof(
			const char *str,
			t_scene *scene);

#endif // PARSER_H

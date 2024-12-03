#include "parser.h"
#include "minirt.h"

t_error	parse_sphere(t_scene *scene, char **line_data)
{
	t_error		errorn;
	t_sphere	*sphere;

	errorn = ERR_NO_ERROR;
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&sphere->vector, line_data[1]);
	if (errorn == ERR_NO_ERROR && is_string_number(line_data[2]))
	{
		sphere->diameter = ft_atof(line_data[2]);
		sphere->radius = sphere->diameter * 0.5;
	}
	else
		errorn = ERR_ATOI_FAILED;
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_color(&sphere->color, line_data[3]);
	if (errorn)
		return (free(sphere), errorn);
	return (scene_add_object(sphere, E_SPHERE, scene));
}

t_error	parse_cylinder(t_scene *scene, char **line_data)
{
	t_error			errorn;
	t_cylinder		*cylinder;

	errorn = ERR_NO_ERROR;
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&cylinder->vector, line_data[1]);
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_vector(&cylinder->axis, line_data[2]);
	if (errorn == ERR_NO_ERROR)
		cylinder->axis = vec3_normalize(cylinder->axis);
	if (is_string_number(line_data[3]) && is_string_number(line_data[4]))
	{
		cylinder->diameter = ft_atof(line_data[3]);
		cylinder->height = ft_atof(line_data[4]);
	}
	else
		errorn = ERR_ATOI_FAILED;
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_color(&cylinder->color, line_data[5]);
	if (errorn)
		return (free(cylinder), errorn);
	return (scene_add_object(cylinder, E_CYLINDER, scene));
}

t_error	parse_plane(t_scene *scene, char **line_data)
{
	t_error	errorn;
	t_plane	*plane;

	errorn = ERR_NO_ERROR;
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&plane->vector, line_data[1]);
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_vector((&plane->axis), line_data[2]);
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_color((&plane->color), line_data[3]);
	if (!errorn)
	{
		plane->axis = vec3_normalize(plane->axis);
		plane->vector = vec3_normalize(plane->vector);
	}
	if (errorn)
		return (free(plane), errorn);
	return (scene_add_object(plane, E_PLANE, scene));
}

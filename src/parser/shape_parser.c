#include "parser.h"
#include "utils.h"

void parse_sphere(t_scene *scene, char **line_data)
{
	t_sphere    *sphere;

	sphere = rt_calloc(1, sizeof(t_sphere), scene);
	if (!sphere)
		return ;
	str_to_vector(&sphere->pos, line_data[1], false, scene);
	sphere->diameter = rt_atof(line_data[2], scene);
	sphere->radius = sphere->diameter * 0.5;
	str_to_color(&sphere->color, line_data[3], scene);
	scene_add_object(sphere, E_SPHERE, scene);
}

void parse_cylinder(t_scene *scene, char **line_data)
{
	t_cylinder	*cylinder;

	cylinder = rt_calloc(1, sizeof(t_cylinder), scene);
	if (!cylinder)
		return ; 
	str_to_vector(&cylinder->pos, line_data[1], false, scene);
	str_to_vector(&cylinder->axis, line_data[2], true, scene);
	cylinder->diameter = rt_atof(line_data[3], scene);
	cylinder->height = rt_atof(line_data[4], scene);
	str_to_color(&cylinder->color, line_data[5], scene);
	scene_add_object(cylinder, E_CYLINDER, scene);
}

void parse_plane(t_scene *scene, char **line_data)
{	
	t_plane	*plane;

	plane = rt_calloc(1, sizeof(t_plane), scene);
	if (!plane)
		return ; 
	str_to_vector(&plane->normal_vec, line_data[1], true, scene);
	str_to_vector((&plane->pos), line_data[2], false, scene);
	str_to_color((&plane->color), line_data[3], scene);
	scene_add_object(plane, E_PLANE, scene);
}

t_error parse_cone(t_scene *scene, char **line_data)
{
	t_error	errorn;
	t_cone	*cone;

	errorn = ERR_NO_ERROR;
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&cone->pos, line_data[1]);
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_vector(&cone->axis, line_data[2]);
	if (errorn == ERR_NO_ERROR)
		cone->axis = vec3_normalize(cone->axis);
	if (is_string_number(line_data[3]) && is_string_number(line_data[4]))
	{
		cone->diameter = ft_atof(line_data[3]);
		cone->height = ft_atof(line_data[4]);
	}
	else
		errorn = ERR_ATOI_FAILED;
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_color(&cone->color, line_data[5]);
	if (errorn)
		return (free(cone), errorn);
	return (scene_add_object(cone, E_CONE, scene));
}
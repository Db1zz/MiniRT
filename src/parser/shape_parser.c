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

void	parse_cone(t_scene *scene, char **line_data)
{
	t_cone	*cone;

	cone = rt_calloc(1, sizeof(t_cone), scene);
	if (!cone)
		return ;
	str_to_vector(&cone->pos, line_data[1], false, scene);
	str_to_vector(&cone->axis, line_data[2], true, scene);
	cone->diameter = rt_atof(line_data[3], scene);
	cone->height = rt_atof(line_data[4], scene);
	str_to_color(&cone->color, line_data[5], scene);
	scene_add_object(cone, E_CONE, scene);
}

// void	parse_cone(t_scene *scene, char **line_data)
// {
// 	t_cone	*cone;

// 	cone = rt_calloc(1, sizeof(t_cone), scene);
// 	if (!cone)
// 		return ;
// 	str_to_vector(&cone->pos, line_data[1], false, scene);
// 	str_to_vector(&cone->axis, line_data[2], true, scene);
// 	cone->diameter = rt_atof(line_data[3], scene);
// 	cone->height = rt_atof(line_data[4], scene);
// 	str_to_color(&cone->color, line_data[5], scene);
// 	scene_add_object(cone, E_CONE, scene);
// }

void	parse_gyper(t_scene *scene, char **line_data)
{
	t_gyper	*gyper;

	gyper = rt_calloc(1, sizeof(t_gyper), scene);
	if (!gyper)
		return ;
	str_to_vector(&gyper->pos, line_data[1], false, scene);
	str_to_vector(&gyper->axis, line_data[2], true, scene);
	str_to_vector(&gyper->squish, line_data[3], true, scene);
	gyper->diameter = rt_atof(line_data[4], scene);
	str_to_color(&gyper->color, line_data[5], scene);
	scene_add_object(gyper, E_GYPER, scene);
}
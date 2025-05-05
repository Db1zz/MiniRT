/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:24 by gonische          #+#    #+#             */
/*   Updated: 2025/05/05 13:44:14 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "minirt_math.h"
#include "libft.h"


void parse_sphere(t_scene *scene, char **line_data)
{
	t_sphere *sphere;
	t_object *object;
	t_aabb	box;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	sphere = rt_calloc(1, sizeof(t_sphere), scene);
	if (!sphere)
		return;
	str_to_vector(&sphere->pos, line_data[1], false, scene);
	sphere->diameter = rt_atof(line_data[2], scene);
	sphere->radius = sphere->diameter * 0.5;
	str_to_color(&sphere->color, line_data[3], scene);
	box = compute_sphere_aabb(sphere);
	object = object_alloc(sphere, box, E_SPHERE, scene->objects_size);
	scene_add_object(scene, object);
}

void	cylinder_init_caps(t_cylinder *cy) {
	t_plane *plane1;
	t_plane *plane2;

	cy->caps = ft_calloc(2, sizeof(t_object));
	plane1 = ft_calloc(1, sizeof(t_plane));
	plane2 = ft_calloc(1, sizeof(t_plane));
	plane1->pos = vec3_mult(cy->pos, 1);
	plane1->normal_vec = vec3_mult(cy->axis, -1);
	plane1->color = cy->color;
	plane2->pos = vec3_add_vec3(cy->pos, vec3_mult(cy->axis, cy->height));
	plane2->normal_vec = cy->axis;
	plane2->color = cy->color;
	cy->caps[0].box = aabb_create_empty();
	cy->caps[0].destructor = NULL;
	cy->caps[0].type = E_PLANE;
	cy->caps[0].type_name = object_get_type_name(cy->caps[0].type);
	cy->caps[0].id = 0;
	cy->caps[1] = cy->caps[0];
	cy->caps[0].data = plane1;
	cy->caps[1].data = plane2;
}

void	parse_cylinder(t_scene *scene, char **line_data)
{
	t_cylinder	*cylinder;
	t_object	*object;
	t_aabb		box;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	cylinder = rt_calloc(1, sizeof(t_cylinder), scene);
	if (!cylinder)
		return;
	str_to_vector(&cylinder->pos, line_data[1], false, scene);
	str_to_vector(&cylinder->axis, line_data[2], true, scene);
	cylinder->diameter = rt_atof(line_data[3], scene);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = rt_atof(line_data[4], scene);
	str_to_color(&cylinder->color, line_data[5], scene);
	cylinder_init_caps(cylinder);
	box = compute_cylinder_aabb(cylinder);
	object = object_alloc(cylinder, box, E_CYLINDER, scene->objects_size);
	scene_add_object(scene, object);
	object->destructor = object_destroy_cylinder;
}

void	parse_plane(t_scene *scene, char **line_data)
{
	t_plane *plane;
	t_object *object;
	t_aabb	box;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	plane = rt_calloc(1, sizeof(t_plane), scene);
	if (!plane)
		return;
	str_to_vector(&plane->normal_vec, line_data[1], true, scene);
	str_to_vector((&plane->pos), line_data[2], false, scene);
	str_to_color((&plane->color), line_data[3], scene);
	box = compute_plane_aabb();
	object = object_alloc(plane, box, E_PLANE, scene->objects_size);
	scene_add_object(scene, object);
}

void	parse_gyper(t_scene *scene, char **line_data)
{
	t_gyper		*gyper;
	t_object	*object;
	t_aabb	box;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	gyper = rt_calloc(1, sizeof(t_gyper), scene);
	if (!gyper)
		return;
	str_to_vector(&gyper->pos, line_data[1], false, scene);
	str_to_vector(&gyper->axis, line_data[2], true, scene);
	str_to_vector(&gyper->squish, line_data[3], true, scene);
	gyper->diameter = rt_atof(line_data[4], scene);
	str_to_color(&gyper->color, line_data[5], scene);
	box = compute_hyperboloid_aabb();
	object = object_alloc(gyper, box, E_GYPER, scene->objects_size);
	scene_add_object(scene, object);
}

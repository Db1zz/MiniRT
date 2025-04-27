/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:24 by gonische          #+#    #+#             */
/*   Updated: 2025/04/14 14:55:57 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "minirt_math.h"

void parse_sphere(t_scene *scene, char **line_data)
{
	t_sphere *sphere;
	t_object *object;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	sphere = rt_calloc(1, sizeof(t_sphere), scene);
	if (!sphere)
		return;
	str_to_vector(&sphere->pos, line_data[1], false, scene);
	sphere->diameter = rt_atof(line_data[2], scene);
	sphere->radius = sphere->diameter * 0.5;
	str_to_color(&sphere->color, line_data[3], scene);
	object = add_object_to_array(sphere, E_SPHERE, scene->objects, &scene->objects_size);
	object->box = compute_sphere_aabb(sphere);
}

void	cylinder_init_caps(t_cylinder *cy) {
	t_plane *cap_plane;
	t_object *cap1;
	t_object *cap2;

	cy->caps = ft_calloc(2, sizeof(t_object));
	cap_plane = ft_calloc(2, sizeof(t_plane));
	cap_plane[0].pos = vec3_mult(cy->pos, 1);
	cap_plane[0].normal_vec = vec3_mult(cy->axis, -1);
	cap_plane[0].color = cy->color;
	cap_plane[1].pos = vec3_add_vec3(cy->pos, vec3_mult(cy->axis, cy->height));
	cap_plane[1].normal_vec = cy->axis;
	cap_plane[1].color = cy->color;
	cap1 = alloc_new_object(&cap_plane[0], E_PLANE);
	cap2 = alloc_new_object(&cap_plane[1], E_PLANE);
	cy->caps[0] = *cap1;
	cy->caps[1] = *cap2;
	(free(cap1), free(cap2));
}

void	parse_cylinder(t_scene *scene, char **line_data)
{
	t_cylinder	*cylinder;
	t_object	*object;

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
	object = add_object_to_array(cylinder, E_CYLINDER, scene->objects, &scene->objects_size);
	object->box = compute_cylinder_aabb(cylinder);
	cylinder_init_caps(cylinder);
}

void	parse_plane(t_scene *scene, char **line_data)
{
	t_plane *plane;
	t_object *object;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	plane = rt_calloc(1, sizeof(t_plane), scene);
	if (!plane)
		return;
	str_to_vector(&plane->normal_vec, line_data[1], true, scene);
	str_to_vector((&plane->pos), line_data[2], false, scene);
	str_to_color((&plane->color), line_data[3], scene);
	object = add_object_to_array(plane, E_PLANE, scene->objects, &scene->objects_size);
	object->box = compute_plane_aabb(plane);
}

void	parse_gyper(t_scene *scene, char **line_data)
{
	t_gyper		*gyper;
	t_object	*object;

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
	object = add_object_to_array(gyper, E_GYPER, scene->objects, &scene->objects_size);
	object->box = compute_hyperboloid_aabb(gyper);
}

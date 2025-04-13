/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:24 by gonische          #+#    #+#             */
/*   Updated: 2025/04/13 18:35:46 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "minirt_math.h"

void parse_sphere(t_scene *scene, char **line_data)
{
	t_sphere *sphere;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	sphere = rt_calloc(1, sizeof(t_sphere), scene);
	if (!sphere)
		return;
	str_to_vector(&sphere->pos, line_data[1], false, scene);
	sphere->diameter = rt_atof(line_data[2], scene);
	sphere->radius = sphere->diameter * 0.5;
	str_to_color(&sphere->color, line_data[3], scene);
	add_object_to_array(sphere, E_SPHERE, scene->objects, &scene->objects_size);
	// ADD New box
	scene->objects[scene->objects_size - 1]
		->box = compute_sphere_aabb(sphere);
	sphere->id = scene->objects_size; // Removeme
	scene->objects[scene->objects_size - 1]->box->aabb_color = create_color(random_double_range(0, 255), random_double_range(0, 255), random_double_range(0, 255));
}

void parse_cylinder(t_scene *scene, char **line_data)
{
	t_cylinder *cylinder;
	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	cylinder = rt_calloc(1, sizeof(t_cylinder), scene);
	if (!cylinder)
		return;
	str_to_vector(&cylinder->pos, line_data[1], false, scene);
	str_to_vector(&cylinder->axis, line_data[2], true, scene);
	cylinder->diameter = rt_atof(line_data[3], scene);
	cylinder->height = rt_atof(line_data[4], scene);
	str_to_color(&cylinder->color, line_data[5], scene);
	add_object_to_array(cylinder, E_CYLINDER, scene->objects, &scene->objects_size);
}

void parse_plane(t_scene *scene, char **line_data)
{
	t_plane *plane;
	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));

	plane = rt_calloc(1, sizeof(t_plane), scene);
	if (!plane)
		return;
	str_to_vector(&plane->normal_vec, line_data[1], true, scene);
	str_to_vector((&plane->pos), line_data[2], false, scene);
	str_to_color((&plane->color), line_data[3], scene);
	add_object_to_array(plane, E_PLANE, scene->objects, &scene->objects_size);
}

void parse_gyper(t_scene *scene, char **line_data)
{
	t_gyper *gyper;
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
	add_object_to_array(gyper, E_GYPER, scene->objects, &scene->objects_size);
}

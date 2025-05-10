/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:14 by gonische          #+#    #+#             */
/*   Updated: 2025/04/13 17:35:02 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "ray_bvh.h"
#include "ray_shapes.h"

#include "light.h"
#include "scene.h"
#include "minirt_math.h"

static t_color	calculate_background_color(const t_ray *ray)
{
	double		a;
	t_vector	color_vec;

	a = 0.5 * (ray->direction.y + 1.0);
	color_vec = vec3_mult(vec3_add_vec3(
				vec3_mult(create_vector(1.0, 1.0, 1.0), 1.0 - a),
				vec3_mult(create_vector(0.5, 0.7, 1), a)),
			255);
	return (create_color(color_vec.x, color_vec.y, color_vec.z));
}

t_color	ray_trace_bvh_color(
	const t_ray *ray,
	const t_bvh_node *tree,
	const t_scene *scene)
{
	t_hit_record	rec;
	t_hit_record	temp;

	init_hit_record(&rec);
	temp = rec;
	if (!ray_hit_bvh(ray, tree, &rec, &temp))
		return (calculate_background_color(ray));
	return (compute_object_illumination(ray, scene, &rec));
}

t_color	ray_trace_array_color(
	const t_ray *ray,
	const t_scene *scene)
{
	t_hit_record	rec;

	init_hit_record(&rec);
	if (!ray_hit_multiple_shapes(ray, (const t_object **)scene->objects, &rec))
		return (calculate_background_color(ray));
	return (compute_object_illumination(ray, scene, &rec));
}

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
#include "light.h"
#include "scene.h"
#include "minirt_math.h"

t_ray create_ray(t_vector origin, t_vector direction, t_color color)
{
	return ((t_ray){origin, direction, color});
}

bool ray_hit_shape(
	const t_ray *ray,
	const t_object *shape,
	t_hit_record *result_rec)
{
	static const ray_hit_shape_funp arr[] = {
		ray_hit_sphere,
		ray_hit_plane,
		ray_hit_cylinder,
		ray_hit_gyper};

	return (arr[(int)shape->type])(ray, shape, result_rec);
}

bool ray_hit_multiple_shapes(
	const t_ray *ray,
	const t_object **shapes,
	t_hit_record *result_rec)
{
	int i;
	bool found;
	t_hit_record closest_rec;
	t_hit_record *closest_rec_ptr;

	i = 0;
	found = false;
	while (shapes[i])
	{
		found = ray_hit_shape(ray, shapes[i], &closest_rec);
		if (found)
			closest_rec_ptr = get_closest_hit(result_rec, &closest_rec);
		++i;
	}
	*result_rec = *closest_rec_ptr;
	return (found);
}

t_color ray_get_background_color(const t_ray *ray)
{
	double a;
	t_vector color_vec;

	a = 0.5 * (ray->direction.y + 1.0);
	color_vec = vec3_mult(vec3_add_vec3(
							  vec3_mult(create_vector(1.0, 1.0, 1.0), 1.0 - a),
							  vec3_mult(create_vector(0.5, 0.7, 1), a)),
						  255);
	return (create_color(color_vec.x, color_vec.y, color_vec.z));
}

bool ray_hit_light(
	const t_ray *light_ray,
	const t_bvh_node *tree,
	t_hit_record *result_rec)
{
	double light_intersect;
	t_hit_record temp_rec;

	init_hit_record(&temp_rec);
	light_intersect = vec3_length(light_ray->direction);
	if (ray_hit_tree_routine(light_ray, tree, result_rec, &temp_rec))
		return (light_intersect <= result_rec->ray_distance - EPSILON);
	return (true);
}

// t_color ray_send(
// 	const t_ray *ray,
// 	const t_scene *scene)
// {
// 	t_hit_record rec;

// 	init_hit_record(&rec);

// 	if (!ray_hit_objects(ray, (const t_object **)scene->objects, &rec))
// 		return (ray_get_background_color(ray));
// 	return (apply_light(ray, scene, &rec));
// }
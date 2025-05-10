/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:27:51 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 02:27:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_light.h"

#include "minirt_math.h" /* FT_EPSILON */
#include "ray_bvh.h" /* is_ray_hit_bvh() */
#include "ray_shapes.h"

t_ray	create_light_ray_from_hit(
	const t_hit_record *shape_rec,
	const t_light *light)
{
	t_vector	ray_origin;
	t_vector	ray_direction;
	double		length;
	t_ray		light_ray;

	ray_origin = hit_record_to_ray_origin(shape_rec);
	ray_direction = vec3_sub_vec3(light->pos, ray_origin);
	length = vec3_length(ray_direction);
	ray_direction = vec3_normalize(ray_direction);
	light_ray = create_ray(ray_origin, ray_direction, light->color, length);
	return (light_ray);
}

bool	light_ray_is_light_visible_in_bvh(
	const t_ray *light_ray,
	const t_bvh_node *tree,
	t_hit_record *result_rec)
{
	t_hit_record	temp_rec;

	init_hit_record(&temp_rec);
	if (ray_hit_bvh(light_ray, tree, result_rec, &temp_rec))
		return (light_ray->length <= result_rec->ray_distance - FT_EPSILON);
	return (true);
}

bool	light_ray_is_light_visible_in_array(
	const t_ray *light_ray,
	const t_object **objects,
	t_hit_record *result_rec)
{
	if (ray_hit_multiple_shapes(light_ray, objects, result_rec))
		return (light_ray->length <= result_rec->ray_distance - FT_EPSILON);
	return (true);
}

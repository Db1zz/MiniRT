/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:03 by gonische          #+#    #+#             */
/*   Updated: 2025/04/13 17:29:30 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt_math.h"
#include "vector.h"
#include "light.h"
#include "libft.h"

void init_hit_record(t_hit_record *rec)
{
	rec->color = create_color(0, 0, 0);
	rec->front_face = false;
	rec->intersection_p = create_vector(0, 0, 0);
	rec->normal = create_vector(0, 0, 0);
	rec->ray_direction = create_vector(0, 0, 0);
	rec->obj_type = E_SPHERE;
	rec->ray_distance = FT_INFINITY;
}

t_hit_record *get_closest_hit(
	t_hit_record *first,
	t_hit_record *second)
{
	if (first->ray_distance > second->ray_distance)
		return (second);
	return (first);
}

t_vector hit_record_to_ray_origin(const t_hit_record *rec)
{
	t_vector origin;

	origin = vec3_add_vec3(rec->intersection_p,
						   vec3_mult(rec->normal, EPSILON));
	return (origin);
}

t_vector get_ray_direction(t_vector origin, t_vector endpoint)
{
	return (vec3_normalize(vec3_sub_vec3(endpoint, origin)));
}

t_ray create_light_ray(
	const t_hit_record *shape_rec,
	const t_light *light)
{
	t_vector ray_origin;
	t_vector ray_direction;
	t_ray light_ray;

	ray_origin = hit_record_to_ray_origin(shape_rec);
	ray_direction = vec3_normalize(vec3_sub_vec3(light->pos, ray_origin));
	light_ray = create_ray(ray_origin, ray_direction, create_color(0, 0, 0));
	return (light_ray);
}

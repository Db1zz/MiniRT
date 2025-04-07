/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_reflections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:07 by gonische          #+#    #+#             */
/*   Updated: 2025/04/03 22:56:39 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "scene.h"
#include "color.h"
#include "light.h"

static t_vector	reflect(t_vector direction, t_vector surf_normal)
{
	const double	dot_product = vec3_dot(direction, surf_normal);

	return (vec3_sub_vec3(direction, vec3_mult(surf_normal, dot_product * 2)));
}

static t_ray	create_reflection_ray(const t_hit_record *hit_rec)
{
	t_vector	origin;
	t_vector	direction;
	t_ray		reflection_ray;

	origin = hit_record_to_ray_origin(hit_rec);
	direction = reflect(hit_rec->ray_direction, hit_rec->normal);
	reflection_ray = create_ray(origin, direction, hit_rec->color);
	return (reflection_ray);
}

static t_color	blend_reflection(
	t_color object_color,
	t_color reflected_light,
	double reflection_intensity)
{
	return (clr_add_clr(
			clr_mult(object_color, 1 - reflection_intensity),
			clr_mult(reflected_light, reflection_intensity)));
}

#define REF_INTENSITY 0.35	

t_color	ray_reflect(
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *rec)
{
	size_t				i;
	t_ray				ref_ray;
	t_hit_record		ref_hit_rec;
	t_color				object_light;
	t_color				ref_light;

	init_hit_record(&ref_hit_rec);
	i = 0;
	while (scene->objects[i])
	{
		ref_ray = create_reflection_ray(rec);
		if (ray_hit_objects(&ref_ray, scene->objects, &ref_hit_rec))
		{
			object_light = apply_light(camera_ray, scene, rec);
			ref_light = apply_light(&ref_ray, scene, &ref_hit_rec);
			return (blend_reflection(object_light, ref_light, REF_INTENSITY));
		}
		++i;
	}
	return (apply_light(camera_ray, scene, rec));
}

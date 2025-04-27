/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:48 by gonische          #+#    #+#             */
/*   Updated: 2025/02/11 18:27:49 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "ray.h"
#include "math.h"

double	calculate_specular_light(
	const t_light *light,
	const t_ray *camera_ray,
	const t_hit_record *hit_rec,
	double specular_reflection_coefficient)
{
	t_vector	halfway_vector;
	t_vector	light_dir;
	t_vector	view_dir;
	double		dot;
	double		specular;

	light_dir = get_ray_direction(light->pos, hit_rec->intersection_p);
	view_dir = get_ray_direction(camera_ray->origin, hit_rec->intersection_p);
	halfway_vector = vec3_normalize(vec3_add_vec3(light_dir, view_dir));
	dot = vec3_dot(hit_rec->normal, halfway_vector);
	specular = pow(dot, 20);
	return (specular * light->ratio * specular_reflection_coefficient);
}

double	get_diffuse_intensity(
	const t_light *light,
	const t_hit_record *shape_rec)
{
	t_vector	light_dir;
	double		diffuse_intensity;
	double		dot;

	light_dir = get_ray_direction(shape_rec->intersection_p, light->pos);
	dot = vec3_dot(shape_rec->normal, light_dir);
	diffuse_intensity = fmax(0, dot) * light->ratio;
	return (diffuse_intensity);
}

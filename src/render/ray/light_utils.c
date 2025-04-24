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

t_vector sample_point_on_light(const t_light *light) {
	t_vector dir = vec3_random_unit_vec();
	return vec3_add_vec3(light->pos, vec3_mult(dir, light->radius));
}

t_ray create_light_ray_sampled(const t_hit_record *rec, const t_light *light)
{
	const t_vector light_pos = sample_point_on_light(light);
	const t_vector dir = vec3_sub_vec3(light_pos, rec->intersection_p);
	const t_ray ray = {
		.origin = vec3_add_vec3(rec->intersection_p, vec3_mult(rec->normal, 1e-4)),
		.direction = vec3_normalize(dir),
		.color = light->color
	};
	return (ray);
}

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
	specular = pow(dot, 70);
	return (specular * light->ratio);
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

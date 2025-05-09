/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:48 by gonische          #+#    #+#             */
/*   Updated: 2025/05/05 16:25:37 by gonische         ###   ########.fr       */
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
	t_vector	reflecton_vec;
	t_vector	light_dir;
	t_vector	view_dir;
	double		dot;
	double		specular[2];

	light_dir = get_ray_direction(hit_rec->intersection_p, light->pos);
	view_dir = get_ray_direction(hit_rec->intersection_p, camera_ray->origin);
	dot = vec3_dot(hit_rec->normal, light_dir);
	reflecton_vec = vec3_sub_vec3(vec3_mult(hit_rec->normal, 2.0 * dot), light_dir);
	reflecton_vec = vec3_normalize(reflecton_vec);
	dot = fmax(0.0, vec3_dot(reflecton_vec, view_dir));
	specular[0] = pow(dot, 12);
	specular[1] = vec3_length(light_dir);
	specular[1] = specular[1] * specular[1];
	return (specular[0] * specular_reflection_coefficient * light->ratio / specular[1]);
}

static double	get_diffuse_intensity(
	const t_light *light,
	const t_hit_record *shape_rec)
{
	t_vector	light_dir;
	double		dot;

	light_dir = get_ray_direction(shape_rec->intersection_p, light->pos);
	dot = vec3_dot(shape_rec->normal, light_dir);
	return (dot * light->ratio);
}

t_color	apply_diffuse_light(
	const t_light *light,
	const t_hit_record *shape_rec)
{
	return (
		clr_mult(shape_rec->color, get_diffuse_intensity(light, shape_rec)));
}

t_color	filter_light(
	const t_light *light,
	const t_hit_record *shape_rec)
{
	t_color px;

	px = clr_mult(
			clr_mult_clr(
				clr_div(shape_rec->color, 255),
				clr_div(light->color, 255)),
			255);
	return (clr_mult(px, get_diffuse_intensity(light, shape_rec)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:44 by gonische          #+#    #+#             */
/*   Updated: 2025/04/28 13:42:49 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "light.h"
#include "ray.h"
#include "math.h"
#include "minirt_math.h"
#include "bvh.h"

static t_color get_specular_light(
	t_light *light,
	const t_ray *camera_ray,
	const t_hit_record *hit_rec)
{
	double coefficient;

	coefficient = calculate_specular_light(light, camera_ray, hit_rec, 0.6);
	return (clr_mult(create_color(255, 255, 255), coefficient));
}

static t_color get_diffuse_light(
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *shape_rec)
{
	t_light *light;
	t_ray light_ray;
	t_hit_record light_ray_rec;
	t_color rc;
	int i;

	i = 0;
	rc = clr_mult(shape_rec->color, 0.1);
	while (scene->lights[i])
	{
		light = scene->lights[i]->data;
		init_hit_record(&light_ray_rec);
		light_ray = create_light_ray(shape_rec, light);
		if (ray_hit_light(&light_ray, scene->tree, &light_ray_rec))
		{
			rc = clr_add_clr(rc, filter_light(light, shape_rec));
			rc = clr_add_clr(rc, get_specular_light(light, camera_ray, shape_rec));
		}
		if (rc.r >= COLOR_MAX && rc.g >= COLOR_MAX && rc.b >= COLOR_MAX)
			break;
		++i;
	}
	rc = normalize_color(rc);
	return (rc);
}

static t_color get_ambient_light(
	const t_object *amb_object,
	const t_hit_record *shape_rec)
{
	const t_amb_lighting *light = (const t_amb_lighting *)amb_object->data;
	t_color px;

	px = clr_mult(
		clr_mult_clr(
			clr_div(shape_rec->color, 255),
			clr_div(light->color, 255)),
		255);
	px = clr_mult(px, light->ratio);
	return (normalize_color(px));
}

t_color apply_light(
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *shape_rec)
{
	t_color	diff_spec_color;
	t_color	ambeint_clr;
	t_color	result_clr;

	diff_spec_color = create_color(0, 0, 0);
	ambeint_clr = create_color(0, 0, 0);
	result_clr = create_color(0, 0, 0);
	if (scene->lights_size)
		diff_spec_color = get_diffuse_light(camera_ray, scene, shape_rec);
	if (scene->ambient_light_size)	
		ambeint_clr = get_ambient_light(scene->ambient_light[0], shape_rec);
	result_clr = clr_add_clr(diff_spec_color, ambeint_clr);
	return (result_clr);
}

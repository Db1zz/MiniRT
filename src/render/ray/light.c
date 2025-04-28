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
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *hit_rec)
{
	double specular;
	t_light *light;
	t_color result_color;
	t_color specular_color;
	int i;

	i = 0;
	result_color = create_color(0, 0, 0);
	specular_color = create_color(255, 255, 255);
	while (scene->lights[i])
	{
		light = scene->lights[i]->data;
		specular = calculate_specular_light(light, camera_ray, hit_rec, 0.6);
		result_color = clr_add_clr(result_color, clr_mult(specular_color, specular));
		++i;
	}
	result_color = normalize_color(result_color);
	return (result_color);
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
	rc = clr_mult(shape_rec->color, 0.15);
	while (scene->lights[i])
	{
		light = scene->lights[i]->data;
		init_hit_record(&light_ray_rec);
		light_ray = create_light_ray(shape_rec, light);
		if (ray_hit_light(&light_ray, scene->tree, &light_ray_rec))
		{
			rc = clr_add_clr(
				clr_mult(
					filter_color(shape_rec->color, light->color),
					get_diffuse_intensity(light, shape_rec)),
				rc);
			rc = clr_add_clr(get_specular_light(camera_ray, scene, shape_rec), rc);
		}
		if (rc.r >= COLOR_MAX && rc.g >= COLOR_MAX && rc.b >= COLOR_MAX)
			break;
		++i;
	}
	rc = normalize_color(rc);
	return (rc);
}

static t_color	get_ambient_light(
	const t_object *amb_object,
	const t_color *color)
{
	const t_amb_lighting *amb_light;
	t_color amb_color;

	amb_light = (const t_amb_lighting *)amb_object->data;
	amb_color = clr_mult(amb_light->color, amb_light->ratio);
	return (normalize_color(clr_add_clr(*color, amb_color)));
}

t_color apply_light(
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *shape_rec)
{
	t_color	result;

	result = create_color(0, 0, 0);
	if (scene->lights[0])
		result = get_diffuse_light(camera_ray, scene, shape_rec);
	// if (scene->ambient_lightings) FIXME
	// 	result = get_ambient_light(scene->ambient_lightings, &result);
	return (result);
}

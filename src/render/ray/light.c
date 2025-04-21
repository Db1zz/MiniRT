/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:44 by gonische          #+#    #+#             */
/*   Updated: 2025/04/14 15:52:22 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "light.h"
#include "ray.h"
#include "math.h"
#include "minirt_math.h"

static t_color get_diffuse_light(
	const t_scene *scene,
	const t_hit_record *shape_rec)
{
	t_light *light;
	t_ray light_ray;
	t_hit_record light_ray_rec;
	t_color result_color;
	int i;

	result_color = create_color(0, 0, 0);
	i = 0;
	while (scene->lights[i])
	{
		light = scene->lights[i]->data;
		init_hit_record(&light_ray_rec);
		light_ray = create_light_ray(shape_rec, light);

		// TODO: traverse tree instead array of objects bro wtf lol
		if (ray_hit_light(&light_ray, (const t_object **)scene->objects, &light_ray_rec))
		{
			result_color = clr_add_clr(
				clr_mult(
					filter_color(shape_rec->color, light->color),
					get_diffuse_intensity(light, shape_rec)),
				result_color);
			result_color = clamp_color(result_color, COLOR_MIN, COLOR_MAX);
		}
		++i;
	}
	return (result_color);
}

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

	result_color = create_color(0, 0, 0);
	specular_color = create_color(255, 255, 255);
		i = 0;
	while (scene->lights[i])
	{
		light = scene->lights[i]->data;
		specular = calculate_specular_light(light, camera_ray, hit_rec, 0.8);
		result_color = clr_add_clr(result_color, clr_mult(specular_color, specular));
		++i;
	}
	result_color = normalize_color(result_color);
	return (result_color);
}

static t_color get_ambient_light(
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
	t_color	specular_light;

	result = create_color(0, 0, 0);
	if (scene->lights[0])
		result = get_diffuse_light(scene, shape_rec);
	// if (scene->ambient_lightings) FIXME
	// 	result = get_ambient_light(scene->ambient_lightings, &result);
	specular_light = get_specular_light(camera_ray, scene, shape_rec);
	result = normalize_color(clr_add_clr(result, specular_light));
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:44 by gonische          #+#    #+#             */
/*   Updated: 2025/05/13 17:02:46 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

#include "light.h" /* t_light | light functions */
#include "ray_light.h" /* create_light_ray_from_hit() */

static t_color	calculate_specular_lighting(
	t_light *light,
	const t_ray *camera_ray,
	const t_hit_record *hit_rec)
{
	double	coefficient;

	coefficient = calculate_specular_intensity(light, camera_ray, hit_rec, 1);
	return (clr_mult(create_color(255, 255, 255), coefficient));
}

#ifdef BONUS

static t_color	get_diffuse_lighting(
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *shape_rec)
{
	t_light			*light;
	t_ray			light_ray;
	t_hit_record	lr_rec;
	t_color			rc;
	int				i;

	i = 0;
	rc = clr_mult(shape_rec->color, 0.05);
	while (scene->lights[i])
	{
		light = scene->lights[i]->data;
		init_hit_record(&lr_rec);
		light_ray = create_light_ray_from_hit(shape_rec, light);
		if (light_ray_is_light_visible_in_bvh(&light_ray, scene->tree, &lr_rec))
		{
			rc = clr_add_clr(rc, apply_light_filter(light, shape_rec));
			rc = clr_add_clr(rc,
					calculate_specular_lighting(light, camera_ray, shape_rec));
		}
		if (rc.r >= COLOR_MAX && rc.g >= COLOR_MAX && rc.b >= COLOR_MAX)
			break ;
		++i;
	}
	rc = normalize_color(rc);
	return (rc);
}

#else // #ifdef BONUS

static t_color	get_diffuse_lighting(
	const t_ray *camera_ray,
	const t_scene *scene,
	const t_hit_record *shape_rec)
{
	t_light			*light;
	t_ray			light_ray;
	t_hit_record	lr_rec;
	t_color			rc;

	if (!scene->lights[0])
		return (create_color(0, 0, 0));
	light = (t_light *)scene->lights[0]->data;
	rc = clr_mult(shape_rec->color, 0.05);
	init_hit_record(&lr_rec);
	light_ray = create_light_ray_from_hit(shape_rec, light);
	if (light_ray_is_light_visible_in_bvh(&light_ray, scene->tree, shape_rec, &lr_rec))
	{
		rc = clr_add_clr(rc, calculate_diffuse_color(light, shape_rec));
		rc = clr_add_clr(rc,
				calculate_specular_lighting(light, camera_ray, shape_rec));
	}
	rc = normalize_color(rc);
	return (rc);
}

#endif

static t_color	get_ambient_lighting(
	const t_object *amb_object,
	const t_hit_record *shape_rec)
{
	const t_amb_lighting	*light = (const t_amb_lighting *)amb_object->data;
	t_color					px;

	px = clr_mult(
			clr_mult_clr(
				clr_div(shape_rec->color, 255),
				clr_div(light->color, 255)),
			255);
	px = clr_mult(px, light->ratio);
	return (normalize_color(px));
}

t_color	compute_object_illumination(
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
		diff_spec_color = get_diffuse_lighting(camera_ray, scene, shape_rec);
	if (scene->ambient_light_size)
		ambeint_clr = get_ambient_lighting(scene->ambient_light[0], shape_rec);
	result_clr = normalize_color(clr_add_clr(diff_spec_color, ambeint_clr));
	return (result_clr);
}

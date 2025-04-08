/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:26:13 by gonische          #+#    #+#             */
/*   Updated: 2025/04/07 19:00:05 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "interval.h"
#include "color.h"
#include "camera.h"

t_color	apply_antialiasing(t_color ray_color, t_scene *scene, int x, int y)
{
	const double		color_scale = (double)(1.0 / SCENE_ANTIALIASING_SAMPLES);
	const t_interval	interval = create_interval(0.0, 255.0);
	int					pixel_samples;

	pixel_samples = 0;
	while (pixel_samples < SCENE_ANTIALIASING_SAMPLES)
	{
		ray_color = clr_add_clr(ray_color,
				camera_get_pixel_color(scene->camera, scene, x, y));
		pixel_samples++;
	}
	ray_color = clr_mult(ray_color, color_scale);
	ray_color.r = interval_clamp(&interval, ray_color.r);
	ray_color.g = interval_clamp(&interval, ray_color.g);
	ray_color.b = interval_clamp(&interval, ray_color.b);
	return (ray_color);
}

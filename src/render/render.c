/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:04:07 by gonische          #+#    #+#             */
/*   Updated: 2025/05/08 14:04:07 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include "camera.h" /* camera_get_pixel_color() */
#include "xpm_render.h" /* xpm_render_put_pixel() */
#include "mlx.h" /* mlx_put_image_to_window() */
#include "viewport.h" /* VIEWPORT_HEIGHT | VIEWPORT_WIDTH */

void	render_scene(t_scene *scene)
{
	size_t	x;
	size_t	y;
	t_color ray_color;

	x = 0;
	while (x < VIEWPORT_HEIGHT)
	{
		y = 0;
		while (y < VIEWPORT_WIDTH)
		{
			ray_color = camera_get_pixel_color(scene->camera, scene, x, y);
			xpm_render_put_pixel(scene->img, x, y, &ray_color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
}

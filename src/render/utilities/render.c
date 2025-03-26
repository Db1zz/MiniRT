/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:21 by gonische          #+#    #+#             */
/*   Updated: 2025/03/26 22:26:02 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"
#include "xpm_render.h"

void	render(t_scene *scene)
{
	unsigned int	x;
	unsigned int	y;
	t_color			ray_color;
	t_xpm_image		img;

	img = xpm_render_new_img(
			scene->mlx,
			WIN_WIDTH, 
			WIN_HEIGHT);
	x = 0;
	while (x < WIN_HEIGHT)
	{
		y = 0;
		while (y < WIN_WIDTH)
		{
			ray_color = camera_get_pixel_color(scene->camera, scene, x, y);
			// ray_color = apply_antialiasing(ray_color, scene, x, y);
			// draw_pixel(scene, x, y, &ray_color);
			xpm_render_put_pixel(&img, x, y, &ray_color);
			y++;
		}
		x++;
	}
	// mlx_put_image_to_window(scene->mlx, scene->win, img.img, 0, 0);
}

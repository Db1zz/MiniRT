/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:21 by gonische          #+#    #+#             */
/*   Updated: 2025/03/27 14:52:32 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"
#include "xpm_render.h"

void	render(t_scene *scene)
{
	int				x;
	int				y;
	t_color			ray_color;
	t_xpm_image img;
	
	x = 0;
	img = xpm_render_new_img(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (x < WIN_HEIGHT)
	{
		y = 0;
		while (y < WIN_WIDTH)
		{
			ray_color = camera_get_pixel_color(scene->camera, scene, x, y);
			ray_color = apply_antialiasing(ray_color, scene, x, y);
			xpm_render_put_pixel(&img, x, y, &ray_color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(img.mlx, scene->win, img.img, 0, 0);
}

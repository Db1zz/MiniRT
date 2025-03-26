/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:21 by gonische          #+#    #+#             */
/*   Updated: 2025/03/26 15:20:20 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"

void	render(t_scene *scene)
{
	int				x;
	int				y;
	t_color			ray_color;
	struct t_img	*img;
	
	img = mlx_new_image(
		scene->mlx,
		scene->camera->viewport.width,
		scene->camera->viewport.height);
	unsigned char *data_addr = mlx_get_data_addr()

	x = 0;
	while (x < WIN_HEIGHT)
	{
		y = 0;
		while (y < WIN_WIDTH)
		{
			ray_color = camera_get_pixel_color(scene->camera, scene, x, y);
			// ray_color = apply_antialiasing(ray_color, scene, x, y);
			mlx_put
			y++;
		}
		x++;
	}
}

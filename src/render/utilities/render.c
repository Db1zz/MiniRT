/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:21 by gonische          #+#    #+#             */
/*   Updated: 2025/04/12 13:06:13 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"
#include "xpm_render.h"
#include "queue.h"

#include <assert.h>

void render(t_scene *scene)
{
	unsigned int x;
	unsigned int y;

	x = 0;
	while (x < VIEWPORT_HEIGHT)
	{
		y = 0;
		while (y < VIEWPORT_WIDTH)
		{
			t_queue_data *qdata = malloc(sizeof(t_queue_data));
			qdata->x = x;
			qdata->y = y;
			queue_push(scene->queue, qdata);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}

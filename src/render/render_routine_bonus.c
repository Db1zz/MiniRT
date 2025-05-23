/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:45:17 by gonische          #+#    #+#             */
/*   Updated: 2025/05/04 01:45:17 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

#include "scene.h" /* scene | viewport macro */
#include "viewport.h" /* VIEWPORT_WIDTH */
#include "camera.h" /* camera_get_pixel_color() */
#include "xpm_render.h" /* xpm_render_put_pixel() */

static void	render_worker_render(t_render_thread_ctx *ctx)
{
	t_xpm_image	*img;
	t_color		ray_color;
	size_t		x;
	size_t		y;

	img = ctx->scene->img;
	x = ctx->start_x;
	while (x < ctx->end_x)
	{
		y = 0;
		while (y < VIEWPORT_WIDTH)
		{
			ray_color = scene_calculate_pixel_color(
					ctx->scene->camera,
					ctx->scene,
					x, y);
			xpm_render_put_pixel(img, x, y, &ray_color);
			++y;
		}
		++x;
	}
}

void	*render_worker_routine(void *render_thread_ctx)
{
	t_render_thread_ctx	*ctx;

	ctx = (t_render_thread_ctx *)render_thread_ctx;
	while (true)
	{
		pepe_barrier_wait(&ctx->sync->render_start_barrier);
		if (ctx->sync->to_finish)
			break ;
		render_worker_render(ctx);
		pepe_barrier_wait(&ctx->sync->render_end_barrier);
	}
	return (NULL);
}

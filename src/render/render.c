/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:45:35 by gonische          #+#    #+#             */
/*   Updated: 2025/05/05 13:00:42 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include "scene.h" /* scene | viewport macro */
#include "timer.h" /* timer */

/*
	This __linux__ block is needed because keyboard events were flooding the event queue
	which, caused in visual distortions and laggy output.
*/
#ifdef __linux__
#include <X11/Xutil.h> /* XSync() */
#include "mlx_int.h" /* (t_xvar *) cast */

/*
	XSync() documentation:
	https://tronche.com/gui/x/xlib/event-handling/XSync.html
*/
static void	display_scene(t_scene *scene)
{
	XSync(((t_xvar *)scene->mlx)->display, True);
	mlx_put_image_to_window(
		scene->mlx, scene->win, scene->img->img, 0, 0);
}

#else
static void	display_scene(t_scene *scene)
{
	mlx_put_image_to_window(
		scene->mlx, scene->win, scene->img->img, 0, 0);
}
#endif

void	render_scene(t_scene *scene, t_render_workers_ctx *workers)
{
	struct timeval start_time;
	struct timeval end_time;

	start_time = getTime();
	pepe_barrier_wait(&workers->sync.render_start_barrier);
	pepe_barrier_wait(&workers->sync.render_end_barrier);
	display_scene(scene);
	end_time = getTime();
	printf("Rendered for [m:%ld, s:%ld, ms:%ld]\n",
		   getMinutesDiff(&start_time, &end_time),
		   getSecondsDiff(&start_time, &end_time),
		   getMilisecondsDiff(&start_time, &end_time));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:45:35 by gonische          #+#    #+#             */
/*   Updated: 2025/05/08 16:38:45 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

#include "scene.h" /* scene | viewport macro */
#include "timer.h" /* timer */
#include "mlx.h" /* mlx_put_image_to_window() */
#include "libft.h" /* ft_printf() */

/*
	This __linux__ block is needed because keyboard events
	were flooding the event queue which,
	caused in visual distortions and laggy output.
*/
#ifdef __linux__
# include <X11/Xutil.h> /* XSync() */
# include "mlx_int.h"   /* (t_xvar *) cast */

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

void	render_scene_bonus(t_scene *scene, t_render_workers_ctx *workers)
{
	pepe_barrier_wait(&workers->sync.render_start_barrier);
	pepe_barrier_wait(&workers->sync.render_end_barrier);
	display_scene(scene);
}

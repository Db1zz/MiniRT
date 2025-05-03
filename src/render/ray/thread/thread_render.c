#include "minirt_threads.h"
#include "timer.h" /* timer */
#include "xpm_render.h" /* t_xpm_image */
#include "scene.h" /* scene | viewport macro */

static void	thread_render(t_ray_thread_ctx *data)
{
	t_xpm_image		*img = data->scene->img;
	t_color			ray_color;
	size_t	x;
	size_t	y;

	x = data->start_x;
	while (x < data->end_x)
	{
		y = 0;
		while (y < VIEWPORT_WIDTH)
		{
			ray_color = camera_get_pixel_color(
				data->scene->camera,
				data->scene,
				x, y);
			xpm_render_put_pixel(img, x, y, &ray_color);
			++y;
		}
		++x;
	}
}

void	*thread_render_routine(void *ray_thread_ctx)
{
	t_ray_thread_ctx	*ctx;
	t_scene				*scene;

	ctx = (t_ray_thread_ctx *)ray_thread_ctx;
	scene = ctx->scene;
	while (true)
	{
		pepe_barrier_wait(&(scene->start_render_barrier));
		thread_render(ctx);
		pepe_barrier_wait(&(scene->end_render_barrier));
	}
	return (NULL);
}

/*
	This __linux__ block is needed because keyboard events were flooding the event queue
	which, caused in visual distortions and laggy output.
*/
#ifdef __linux__
# include <X11/Xutil.h>
# include "mlx_int.h"

/*
	XSync() documentation:
	https://tronche.com/gui/x/xlib/event-handling/XSync.html
*/
static void	display_image(t_scene *scene)
{
	XSync(((t_xvar *)scene->mlx)->display, True);
	mlx_put_image_to_window(
		scene->mlx, scene->win, scene->img->img, 0, 0);
}

# else
static void	display_image(t_scene *scene)
{
	mlx_put_image_to_window(
		scene->mlx, scene->win, scene->img->img, 0, 0);
}
#endif

void	thread_render_image(t_scene *scene)
{
	struct timeval start_time = getTime();
	pepe_barrier_wait(&(scene->start_render_barrier));
	pepe_barrier_wait(&(scene->end_render_barrier));
	display_image(scene);
	struct timeval end_time = getTime();
	printf("Rendered for [m:%ld, s:%ld, ms:%ld]\n",
		   getMinutesDiff(&start_time, &end_time),
		   getSecondsDiff(&start_time, &end_time),
		   getMilisecondsDiff(&start_time, &end_time));
}

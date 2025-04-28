#include "minirt_threads.h"
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

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

static void	*thread_render_routine(void *ray_thread_ctx)
{
	t_ray_thread_ctx	*data;
	t_scene				*scene;

	data = (t_ray_thread_ctx *)ray_thread_ctx;
	scene = data->scene;
	while (true)
	{
		pthread_mutex_lock(&data->thread_lock);
		thread_render(data);
		pthread_mutex_lock(&scene->global_mutex);
		++scene->tasks_fineshed;
		pthread_mutex_unlock(&scene->global_mutex);
	}
	return (NULL);
}

bool	init_threads(t_scene *scene)
{
	t_ray_thread_ctx	*threads_ctx;
	size_t				i;
	size_t				perv_end;

	i = 0;
	pthread_mutex_init(&scene->global_mutex, NULL);
	scene->threads_amount = sysconf(_SC_NPROCESSORS_CONF);
	scene->threads_ctx = ft_calloc(scene->threads_amount, sizeof(t_ray_thread_ctx));
	scene->tasks_fineshed = 0;
	threads_ctx = scene->threads_ctx;
	perv_end = 0;
	while (i < scene->threads_amount)
	{
		pthread_mutex_init(&threads_ctx[i].thread_lock, NULL);
		pthread_mutex_lock(&threads_ctx[i].thread_lock);
		threads_ctx[i].start_x = perv_end;
		threads_ctx[i].end_x = perv_end + (VIEWPORT_HEIGHT / scene->threads_amount + ((VIEWPORT_HEIGHT - perv_end) % (scene->threads_amount - i)));
		threads_ctx[i].scene = scene;
		threads_ctx[i].tid = i;
		perv_end = threads_ctx[i].end_x;
		printf("thread[%zu].render_start: %zu, thread[%zu].render_end: %zu\n", i, threads_ctx[i].start_x, i, threads_ctx[i].end_x);
		pthread_create(&scene->threads_ctx[i].pt, NULL, thread_render_routine, &threads_ctx[i]);
		++i;
	}
	return (true);
}

void	threads_render_image(t_scene *scene)
{
	unlock_threads(scene->threads_ctx, scene->threads_amount);
	while (true)
	{
		pthread_mutex_lock(&scene->global_mutex);
		if (scene->tasks_fineshed == scene->threads_amount)
		{
			pthread_mutex_unlock(&scene->global_mutex);
			break;
		}
		pthread_mutex_unlock(&scene->global_mutex);
		usleep(1000);
	}
	printf("Displaying img\n");
	mlx_put_image_to_window(
		scene->mlx, scene->win, scene->img->img, 0, 0);
	scene->tasks_fineshed = 0;
}

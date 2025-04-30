#include "minirt_threads.h"
#include "timer.h"

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
		sem_wait(scene->thread_task_sem);
		thread_render(data);
		sem_wait(scene->global_sem);
		++scene->tasks_fineshed;
		sem_post(scene->global_sem);
	}
	return (NULL);
}

static bool	threads_init_semaphores(t_scene *scene)
{
	size_t	ta = scene->threads_amount;

	init_semaphore(&scene->global_sem, MINIRT_GLOBAL_SEM_NAME, 1);
	init_semaphore(&scene->thread_task_sem, MINIRT_THREAD_SEM_NAME, 0);
	return (scene->global_sem && scene->thread_task_sem);
}

bool	init_threads(t_scene *scene)
{
	t_ray_thread_ctx	*threads_ctx;
	size_t				i;
	size_t				perv_end;

	i = 0;
	scene->threads_amount = sysconf(_SC_NPROCESSORS_CONF);
	printf("CPU: %zu\n", scene->threads_amount);
	scene->threads_ctx = ft_calloc(scene->threads_amount, sizeof(t_ray_thread_ctx));
	scene->tasks_fineshed = 0;
	threads_ctx = scene->threads_ctx;
	perv_end = 0;
	if (!threads_init_semaphores(scene))
		return (free(scene->threads_ctx), false);
	while (i < scene->threads_amount)
	{
		threads_ctx[i].start_x = perv_end;
		threads_ctx[i].end_x = perv_end + (VIEWPORT_HEIGHT / scene->threads_amount + ((VIEWPORT_HEIGHT - perv_end) % (scene->threads_amount - i)));
		threads_ctx[i].scene = scene;
		threads_ctx[i].tid = i;
		perv_end = threads_ctx[i].end_x;
		printf("thread[%zu]render_start: %zu, thread[%zu]render_end: %zu\n", i, threads_ctx[i].start_x, i, threads_ctx[i].end_x);
		pthread_create(&scene->threads_ctx[i].pt, NULL, thread_render_routine, &threads_ctx[i]);
		++i;
	}
	return (true);
}

void	threads_render_image(t_scene *scene)
{
	struct timeval start_time = getTime();
	scene->tasks_fineshed = 0;
	semaphore_increment(scene->thread_task_sem, scene->threads_amount);
	while (true)
	{
		sem_wait(scene->global_sem);
		if (scene->tasks_fineshed == scene->threads_amount)
		{
			sem_post(scene->global_sem);
			break;
		}
		sem_post(scene->global_sem);
		usleep(1000);
	}
	mlx_put_image_to_window(
		scene->mlx, scene->win, scene->img->img, 0, 0);
	struct timeval end_time = getTime();
	printf("Rendered for [m:%ld, s:%ld, ms:%ld]\n",
		   getMinutesDiff(&start_time, &end_time),
		   getSecondsDiff(&start_time, &end_time),
		   getMilisecondsDiff(&start_time, &end_time));
}

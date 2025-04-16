#include "minirt_threads.h"
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

static void thread_render(t_ray_thread_ctx *data)
{
	t_color ray_color;
	unsigned int x;
	unsigned int y;

	x = data->x_start;
	while (x < data->x_end)
	{
		y = 0;
		while (y < VIEWPORT_WIDTH)
		{
			ray_color = camera_get_pixel_color(
				data->scene->camera,
				data->scene,
				x, y);
			xpm_render_put_pixel(&data->scene->img, x, y, &ray_color);
			y++;
		}
		x++;
	}
}

void *ray_task_handler(void *ray_thread_ctx)
{
	t_ray_thread_ctx *data;
	t_scene *scene;

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

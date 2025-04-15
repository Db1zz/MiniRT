#include "minirt_threads.h"
#include <stdlib.h>
#include <assert.h>

void *ray_task_handler(void *ray_thread_ctx)
{
	t_ray_thread_ctx *data;

	data = (t_ray_thread_ctx *)ray_thread_ctx;
	assert(data->scene->queue != NULL);

	while (true) {
		if (!pthread_mutex_lock(&data->queue_mutex)) {
			t_queue_data *queue_data = queue_pop(data->scene->queue);
			pthread_mutex_unlock(&data->queue_mutex);
			if (queue_data) {
				t_color pixel_color =
					camera_get_pixel_color(data->scene->camera, data->scene, queue_data->x, queue_data->y);
				xpm_render_put_pixel(&data->scene->img, queue_data->x, queue_data->y, &pixel_color);
				free(queue_data);
			}
		}
	}
	return (NULL);
}

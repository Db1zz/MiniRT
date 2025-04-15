#include "minirt_threads.h"

/*
	we're going to create a thread pool for every single ray
	in pipeline.

	camera_ray
	shadow_ray
	reflection_ray

	pipeline:
	camera_ray->shadow_ray->reflection_ray->pixel_color
*/
void *ray_task_handler(void *ray_thread_ctx)
{
	t_ray_thread_ctx *data;

	data = (t_ray_thread_ctx *)ray_thread_ctx;
}

#ifndef MINIRT_THREADS_H
# define MINIRT_THREADS_H

#include "ray.h"
#include "minirt.h"
#include <pthread.h>

typedef struct s_ray_thread_ctx
{
	t_scene	*scene;
	
}	t_ray_thread_ctx;

void *ray_task_handler(void *ray_thread_ctx);

#endif // MINIRT_THREADS_H
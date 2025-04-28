#ifndef MINIRT_THREADS_H
# define MINIRT_THREADS_H

# include "ray.h"
# include "minirt.h"
# include "queue.h"
# include "bvh.h"

# include <pthread.h>

typedef struct s_ray_thread_ctx
{
	t_scene			*scene;
	pthread_mutex_t	thread_lock;
	pthread_t		pt;
	size_t			start_x;
	size_t			end_x;
	size_t			tid;
}	t_ray_thread_ctx;

void	unlock_threads(t_ray_thread_ctx *threads_ctx, size_t threads_amount);
void	lock_threads(t_ray_thread_ctx *threads_ctx, size_t threads_amount);
bool	init_threads(t_scene *scene);
void	threads_render_image(t_scene *scene);

#endif // MINIRT_THREADS_H
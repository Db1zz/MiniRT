#include "minirt_threads.h"

#include <pthread.h>

void	unlock_threads(t_ray_thread_ctx *threads_ctx, size_t threads_amount)
{
	size_t	i;

	i = 0;
	while (i < threads_amount) {
		pthread_mutex_unlock(&threads_ctx[i].thread_lock);
		++i;
	}
}

void	lock_threads(t_ray_thread_ctx *threads_ctx, size_t threads_amount)
{
	size_t	i;

	i = 0;
	while (i < threads_amount) {
		pthread_mutex_lock(&threads_ctx[i].thread_lock);
		++i;
	}
}

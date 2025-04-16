#ifndef MINIRT_THREADS_H
# define MINIRT_THREADS_H

#include "ray.h"
#include "minirt.h"
#include "queue.h"
#include "bvh.h"

#include <pthread.h>
#include <semaphore.h>

typedef struct s_ray_thread_ctx
{
	int		x_start;
	int		x_end;
	t_scene	*scene;
}	t_ray_thread_ctx;

void	*ray_task_handler(void *ray_thread_ctx);
bool	open_semaphore(sem_t **sem, char *sem_name, int sem_size);
void	init_semaphore(sem_t **sem, char *sem_name, int sem_size);
void	close_semaphore(sem_t *sem);

#endif // MINIRT_THREADS_H
#ifndef MINIRT_THREADS_H
# define MINIRT_THREADS_H

# include "ray.h"
# include "queue.h"
# include "bvh.h"

# include <pthread.h>
# include <semaphore.h>

# define MINIRT_THREAD_SEM_NAME "minirt_thread_task_sem"
# define MINIRT_GLOBAL_SEM_NAME "minirt_global_sem"

typedef struct s_ray_thread_ctx
{
	t_scene		*scene;
	pthread_t	pt;
	size_t		start_x;
	size_t		end_x;
	size_t		tid;
}	t_ray_thread_ctx;

typedef struct s_thread_sync
{
	bool	exit_threads;
	size_t	tasks_fineshed;
}	t_thread_sync;

bool	open_semaphore(sem_t **sem, const char *sem_name, int sem_size);
bool	init_semaphore(sem_t **sem, const char *sem_name, int sem_size);
void	close_semaphore(sem_t *sem);
void	semaphore_decrement(sem_t *sem, size_t sem_amount);
void	semaphore_increment(sem_t *sem, size_t sem_amount);
bool	init_threads(t_scene *scene);
void	threads_render_image(t_scene *scene);

#endif // MINIRT_THREADS_H
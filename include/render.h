#ifndef RENDER_H
# define RENDER_H

# include "pepe_barrier.h"
# include "scene.h" /* t_scene */

# include <pthread.h>
# include <stdbool.h>

typedef struct s_render_sync
{
	t_pepe_barrier render_start_barrier;
	t_pepe_barrier render_end_barrier;
	bool to_finish;
}	t_render_sync;

typedef struct s_render_thread_ctx
{
	t_scene *scene;
	pthread_t pt;
	size_t start_x;
	size_t end_x;
	size_t tid;
	t_render_sync *sync;
}	t_render_thread_ctx;

typedef struct s_render_workers_ctx
{
	t_render_thread_ctx *threads;
	t_render_sync sync;
	size_t num_threads;
} 	t_render_workers_ctx;

void render_init_workers(
	t_render_workers_ctx *workers,
	size_t num_workers,
	t_scene *scene);

void	render_spawn_workers(t_render_workers_ctx *workers);

void	render_destroy_workers(t_render_workers_ctx *workers);

void	*render_worker_routine(void *render_thread_ctx);

void	render_scene(t_scene *scene, t_render_workers_ctx *workers);

#endif  // RENDER_H
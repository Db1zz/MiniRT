/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:55:13 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:55:13 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

# include "pepe_barrier.h" /* pepe barrier */
# include "scene.h" /* t_scene */

# include <pthread.h> /* pthread_t */
# include <stdbool.h>

typedef struct s_render_sync
{
	t_pepe_barrier	render_start_barrier;
	t_pepe_barrier	render_end_barrier;
	bool			to_finish;
}	t_render_sync;

typedef struct s_render_thread_ctx
{
	t_scene			*scene;
	t_render_sync	*sync;
	pthread_t		pt;
	size_t			start_x;
	size_t			end_x;
	size_t			tid;
}	t_render_thread_ctx;

typedef struct s_render_workers_ctx
{
	t_render_sync		sync;
	t_render_thread_ctx	*threads;
	size_t				num_threads;
}	t_render_workers_ctx;

void	render_init_workers(
			t_render_workers_ctx *workers,
			size_t num_workers,
			t_scene *scene);

void	render_spawn_workers(t_render_workers_ctx *workers);

void	render_destroy_workers(t_render_workers_ctx *workers);

void	*render_worker_routine(void *render_thread_ctx);

void	render_scene_bonus(t_scene *scene, t_render_workers_ctx *workers);

#endif  // RENDER_BONUS_H

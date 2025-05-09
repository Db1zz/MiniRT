/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_workers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:44:58 by gonische          #+#    #+#             */
/*   Updated: 2025/05/05 13:57:37 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_bonus.h"

#include "scene.h" /* scene */
#include "libft.h" /* ft_calloc() */

#include <sys/types.h> /* sysconf */
#include <stdlib.h> /* free() */

void	render_init_workers(
	t_render_workers_ctx *workers,
	size_t num_workers,
	t_scene *scene)
{
	size_t	i;
	size_t	perv_end;
	size_t	base;
	size_t	remainder;

	i = 0;
	workers->num_threads = num_workers;
	pepe_barrier_init(&workers->sync.render_start_barrier, NULL, num_workers+1);
	pepe_barrier_init(&workers->sync.render_end_barrier, NULL, num_workers+1);
	workers->sync.to_finish = false;
	workers->threads = ft_calloc(num_workers, sizeof(t_render_thread_ctx));
	base = VIEWPORT_HEIGHT / num_workers;
	remainder = VIEWPORT_HEIGHT % num_workers;
	perv_end = 0;
	while (i < num_workers)
	{
		workers->threads[i].start_x = perv_end;
		workers->threads[i].end_x = perv_end + base;
		if (i < remainder)
			workers->threads[i].end_x += 1;
		perv_end = workers->threads[i].end_x;
		workers->threads[i].tid = i;
		workers->threads[i].scene = scene;
		workers->threads[i].sync = &workers->sync;
		++i;
	}
}

void	render_spawn_workers(t_render_workers_ctx *workers)
{
	size_t	i;

	i = 0;
	while (i < workers->num_threads)
	{
		pthread_create(&(workers->threads[i].pt),
			NULL,
			render_worker_routine,
			&workers->threads[i]);
			++i;
	}
}

void	render_destroy_workers(t_render_workers_ctx *workers)
{
	size_t	i;

	i = 0;
	workers->sync.to_finish = true;
	pepe_barrier_wait(&workers->sync.render_start_barrier);
	while (i < workers->num_threads)
	{
		pthread_join(workers->threads[i].pt, NULL);
		++i;
	}
	pepe_barrier_destroy(&workers->sync.render_start_barrier);
	pepe_barrier_destroy(&workers->sync.render_end_barrier);
	free(workers->threads);
}

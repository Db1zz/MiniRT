/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:21 by gonische          #+#    #+#             */
/*   Updated: 2025/04/16 22:57:42 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"
#include "xpm_render.h"
#include "queue.h"

#include <assert.h>
#include <unistd.h>

void	semaphore_decrement(sem_t *sem, size_t sem_amount) {
	size_t	i;

	i = 0;
	while (i < sem_amount) {
		sem_wait(sem);
		++i;
	}
}

void semaphore_increment(sem_t *sem, size_t sem_amount) {
	size_t i;

	i = 0;
	while (i < sem_amount)
	{
		sem_post(sem);
		++i;
	}
}

void render(t_scene *scene)
{
	scene->tasks_fineshed = 0;
	semaphore_increment(scene->thread_task_sem, scene->threads_amount);

	while (true)
	{
		sem_wait(scene->global_sem);
		if (scene->tasks_fineshed == scene->threads_amount)
		{
			sem_post(scene->global_sem);
			break;
		}
		sem_post(scene->global_sem);
		usleep(1000);
	}

	mlx_put_image_to_window(
		scene->mlx, scene->win, scene->img.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pepe_barrier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:23:27 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 15:55:00 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pepe_barrier.h"

#include <stdlib.h> /* malloc | free */
#include <unistd.h> /* usleep */

int	pepe_barrier_init(
	t_pepe_barrier *barrier,
	pthread_mutexattr_t *mutex_attr,
	int thread_barrier_number)
{
	int	err_no;

	barrier->total_thread = 0;
	barrier->thread_barrier_number = thread_barrier_number;
	barrier->barrier_locked = true;
	err_no = pthread_mutex_init(&barrier->lock, mutex_attr);
	if (err_no)
		return (err_no);
	return (EXIT_SUCCESS);
}

int	pepe_barrier_destroy(t_pepe_barrier *barrier)
{
	return (pthread_mutex_destroy(&(barrier->lock)));
}

void	pepe_barrier_wait(t_pepe_barrier *barrier)
{
	if (!pthread_mutex_lock(&(barrier->lock)))
	{
		barrier->total_thread += 1;
		if (barrier->total_thread == barrier->thread_barrier_number)
			barrier->barrier_locked = false;
		pthread_mutex_unlock(&(barrier->lock));
	}
	while (barrier->barrier_locked)
		usleep(1000);
	if (!pthread_mutex_lock(&(barrier->lock)))
	{
		barrier->total_thread -= 1;
		if (barrier->total_thread == 0)
			barrier->barrier_locked = true;
		pthread_mutex_unlock(&(barrier->lock));
	}
}

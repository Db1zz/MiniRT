/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pepe_barrier.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:44:26 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:44:26 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PEPE_BARRIER_H
# define PEPE_BARRIER_H

# include <pthread.h> /* pthread_mutex_* */
# include <stdbool.h> /* bool */

typedef struct s_pepe_barrier
{
	pthread_mutex_t	lock;
	int				total_thread;
	int				thread_barrier_number;
	bool			barrier_locked;
}	t_pepe_barrier;

void	pepe_barrier_wait(t_pepe_barrier *barrier);

int		pepe_barrier_init(
			t_pepe_barrier *barrier,
			pthread_mutexattr_t *mutex_attr,
			int thread_barrier_number);

int		pepe_barrier_destroy(t_pepe_barrier *barrier);

#endif  // PEPE_BARRIER_H
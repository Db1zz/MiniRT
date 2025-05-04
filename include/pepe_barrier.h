#ifndef PEPE_BARRIERS_H
# define PEPE_BARRIERS_H

#include <pthread.h> /* pthread_mutex_* */
#include <stdbool.h> /* bool */

typedef struct s_pepe_barrier
{
	pthread_mutex_t	lock;
	int total_thread;
	int thread_barrier_number;
	bool barrier_locked;
}	t_pepe_barrier;

int pepe_barrier_init(
	t_pepe_barrier *barrier,
	pthread_mutexattr_t *mutex_attr,
	int thread_barrier_number);

int pepe_barrier_destroy(t_pepe_barrier *barrier);

void pepe_barrier_wait(t_pepe_barrier *barrier);

#endif  // PEPE_BARRIERS_H
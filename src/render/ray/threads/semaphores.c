#include "minirt_threads.h"
#include <fcntl.h>		/* For O_* constants */
#include <sys/stat.h>	/* For mode constants */

bool open_semaphore(sem_t **sem, const char *sem_name, int sem_size)
{
	const char *msg_err_issuer = "open_semaphore Error:";

	if (sem_name == NULL)
	{
		printf("%s sem_name is NULL\n", msg_err_issuer);
		return (false);
	}
	if (sem_size < 0)
	{
		printf("%s sem_size cannot be < 0\n", msg_err_issuer);
		return (false);
	}
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, sem_size);
	if (*sem == NULL)
	{
		printf("%s cannot open semaphore\n", msg_err_issuer);
		return (false);
	}
	return (true);
}

bool 	init_semaphore(sem_t **sem, const char *sem_name, int sem_size)
{
	sem_unlink(sem_name);
	return (open_semaphore(sem, sem_name, sem_size));
}

void	close_semaphore(sem_t *sem)
{
	const char *msg_err_issuer = "close_semaphore Error:";

	if (sem_close(sem))
		printf("%s sem_close failed\n", msg_err_issuer);
}

void	semaphore_decrement(sem_t *sem, size_t sem_amount)
{
	size_t i;

	i = 0;
	while (i < sem_amount)
	{
		sem_wait(sem);
		++i;
	}
}

void	semaphore_increment(sem_t *sem, size_t sem_amount)
{
	size_t i;

	i = 0;
	while (i < sem_amount)
	{
		sem_post(sem);
		++i;
	}
}

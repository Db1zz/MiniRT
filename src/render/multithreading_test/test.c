#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

typedef struct s_data {
	int data;
}	t_data;

void *test_function(void *thread_data)
{
	t_data *data = (t_data *)thread_data;
	for (int i = 0; i < INT_MAX; ++i) {
		printf("%d\n", i);
	}
	return (NULL);
}

int main(int argc, char **argv) {
	pthread_t		thread;
	pthread_attr_t	attr;
	t_data			data;
	void			*ret_from_thread;
	data.data = 10;

	pthread_create(&thread, NULL, test_function, &data);
	pthread_join(thread, NULL);
	printf("finished\n");
	return (0);
}
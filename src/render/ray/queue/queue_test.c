#define QUEUE_QUEUE_DATA

#include <stdio.h>
#include "queue.h"

typedef int t_queue_data;


/*
	cc -o test queue.c queue_test.c queue_utils.c ../../../../libft/libft.a -I ../../../../include -I ../../../../libft
*/

int main(void) {
	t_queue *queue = queue_init();
	t_queue_data data1 = 1;
	t_queue_data data2 = 2;
	t_queue_data data3 = 3;
	t_queue_data data4 = 4;
	t_queue_data data5 = 5;

	queue_push(queue, &data1);
	queue_push(queue, &data2);
	queue_push(queue, &data3);
	queue_push(queue, &data4);
	queue_push(queue, &data5);
	printf("queue_size:%zu\n", queue->size);
	printf("first: %d\n",*queue->first->data);
	printf("last: %d\n", *queue->last->data);

	queue_pop(queue);
	printf("queue_size:%zu\n", queue->size);
	for (t_queue_node *i = queue->first; i; i = i->next) {
		printf("data: %d\n", *i->data);
	}

	queue_destroy(&queue);
	return 0;
}
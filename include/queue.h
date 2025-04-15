#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h> // size_t

typedef int t_queue_data;

typedef struct s_queue_node {
	t_queue_data *data;
	struct s_queue_node *next;
}	t_queue_node;

typedef struct s_queue {
	size_t			size;
	t_queue_node	*first;
	t_queue_node	*last;
}	t_queue;

t_queue			*queue_init();
void			queue_push(t_queue *queue, t_queue_data *data);
t_queue_data	*queue_pop(t_queue *queue);
t_queue_node	*queue_create_node(t_queue_data *data, t_queue_node *next);
void			queue_free_node(t_queue_data *data);

#endif // QUEUE_H
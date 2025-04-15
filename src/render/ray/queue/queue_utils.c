#include "queue.h"

void queue_free_node(t_queue_node **node)
{
	free(*node);
	*node = NULL;
}

t_queue_node *queue_create_node(t_queue_data *data, t_queue_node *next)
{
	t_queue_node *new_node;

	new_node = malloc(sizeof(t_queue_node));
	new_node->data = data;
	new_node->next = next;

	return (new_node);
}

#include "queue.h"
#include "libft.h"

#include <assert.h>

t_queue	*queue_init()
{
	t_queue	*queue;

	queue = ft_calloc(1, sizeof(t_queue));
	queue->first = NULL;
	queue->last = NULL;

	return (queue);
}

void	queue_push(t_queue *queue, t_queue_data *data){
	t_queue_node	*node;

	node = queue_create_node(data, NULL);
	if (queue->last)
		queue->last->next = node;
	if (queue->size == 0) 
		queue->first = node;
	queue->last = node;
	++queue->size;
}

t_queue_data *queue_pop(t_queue *queue)
{
	t_queue_node	*first;
	t_queue_data	*data;

	if (queue->size == 0) {
		return (NULL);
	}

	first = queue->first;
	if (first->next)
		queue->first = first->next;
	else {
		queue->first = NULL;
		queue->last = NULL;
	}
	data = first->data;
	--(queue->size);
	free(first);
	return (data);
}

void	queue_destroy(t_queue **queue) {
	t_queue *temp;
	t_queue_node	*node_to_free;

	assert(queue != NULL);
	temp = *queue;
	assert(temp != NULL);

	if (temp->size > 0)
	{
		while (temp->first)
		{
			node_to_free = temp->first;
			temp->first = temp->first->next;
			queue_free_node(&node_to_free);
		}
	}
	free(*queue);
	*queue = NULL;
}

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

void queue_push(t_queue *queue, t_queue_data *data){
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

// Destroy queue xd TODO
void	queue_destroy(t_queue **queue) {
	t_queue *temp;

	temp = *queue;
	assert(temp != NULL);

	if (temp->data) {
		free(temp->data);
		temp->data = NULL;
	}
	free(temp);

	*queue = NULL;
}

t_queue_node	*queue_create_node(t_queue_data *data, t_queue_node *next) {
	t_queue_node	*new_node;

	new_node = malloc(sizeof(data));
	new_node->data = data;
	new_node->next = next;

	return (new_node);
}

void queue_free_node(t_queue_data *data) {

}
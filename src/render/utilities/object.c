#include "object.h"
#include <stdlib.h>

t_object_list	*alloc_new_object(
	void			*data,
	t_object_type	type,
	t_object_list	*next)
{
	t_object_list	*new_object;

	new_object = malloc(sizeof(t_object_list));
	new_object->data = data;
	new_object->type = type;
	new_object->next = next;
	return (new_object);
}

void	object_add_back(t_object_list *new, t_object_list **list)
{
	t_object_list	*tail;

	if (!list)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
}

void	free_object(t_object_list **object)
{
	if (!object || !*object)
		return ;
	if ((*object)->data)
		free((*object)->data);
	free(*object);
	*object = NULL;
}

void	free_object_list(t_object_list **list)
{
	t_object_list	*tail;
	t_object_list	*to_free;

	if (!list || !*list)
		return ;
	tail = *list;
	while (tail)
	{
		to_free = tail;
		tail = tail->next;
		free_object(&to_free);
	}
	*list = NULL;
}

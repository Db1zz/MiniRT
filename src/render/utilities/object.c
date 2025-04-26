/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:08 by gonische          #+#    #+#             */
/*   Updated: 2025/04/08 18:40:40 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include <stdlib.h>

t_object	*alloc_new_object(
	void			*data,
	t_object_type	type)
{
	t_object	*new_object;

	new_object = ft_calloc(1, sizeof(t_object));
	new_object->data = data;
	new_object->type = type;
	new_object->type_name = get_object_type_name(type);
	new_object->box = NULL;
	new_object->id = -1;
	return (new_object);
}

const char *get_object_type_name(t_object_type type) {
	static const char *strs[] = {
		"Sphere",
		"Cylinder",
		"Gyper",
		"Light",
		"Ambient Light"
	};

	return (strs[(int)type]);
}

void	init_object(
	t_object *object,
	void *data,
	t_object_type type)
{
	object->data = data;
	object->type = type;
}

void	free_object(t_object **object)
{
	if (!object || !*object)
		return ;
	if ((*object)->data) {
		free((*object)->data);		
	}
	if ((*object)->box) {
		free((*object)->box);
	}

	free(*object);
	*object = NULL;
}
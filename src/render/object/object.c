/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:08 by gonische          #+#    #+#             */
/*   Updated: 2025/05/05 13:56:57 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

#include "libft.h" /* ft_calloc() */

#include <stdlib.h> /* free() */

t_object *object_alloc(
	void *data,
	t_aabb box,
	t_object_type type,
	size_t id)
{
	t_object	*new_object;

	new_object = ft_calloc(1, sizeof(t_object));
	new_object->data = data;
	new_object->type = type;
	new_object->type_name = object_get_type_name(type);
	new_object->box = box;
	new_object->id = id;
	new_object->destructor = NULL;
	return (new_object);
}

const char *object_get_type_name(t_object_type type) {
	static const char *strs[] = {
		"Sphere",
		"Cylinder",
		"Plane",
		"Gyper",
		"Light",
		"Ambient Light"
	};

	return (strs[(int)type]);
}

void	object_destroy(t_object **object)
{
	if (!object || !*object)
		return ;
	if ((*object)->destructor)
		(*object)->destructor(*object);
	else
	{
		if ((*object)->data)
			free((*object)->data);
		free(*object);
	}
	*object = NULL;
}

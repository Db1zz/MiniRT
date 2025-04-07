/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:08 by gonische          #+#    #+#             */
/*   Updated: 2025/04/03 22:22:28 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>

t_object	*alloc_new_object(
	void			*data,
	t_object_type	type)
{
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	new_object->data = data;
	new_object->type = type;
	return (new_object);
}

void	free_object(t_object **object)
{
	if (!object || !*object)
		return ;
	if ((*object)->data)
		free((*object)->data);
	free(*object);
	*object = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:45:56 by gonische          #+#    #+#             */
/*   Updated: 2025/05/04 01:45:56 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static t_error	scene_add(
	t_object **array,
	size_t *array_size,
	size_t array_max_size,
	t_object *object_to_add)
{
	if (*array_size >= array_max_size)
		return (create_error(ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));
	array[(*array_size)] = object_to_add;
	(*array_size) += 1;
	array[(*array_size)] = NULL;
	return (create_error(ERR_NO_ERROR, NULL));
}

t_error	scene_add_object(t_scene *scene, t_object *object)
{
	return (scene_add(
			scene->objects,
			&(scene->objects_size),
			SCENE_OBJECTS_LIMIT,
			object));
}

t_error	scene_add_light(t_scene *scene, t_object *light)
{
	return (scene_add(
			scene->lights,
			&(scene->lights_size),
			SCENE_LIGHTS_LIMIT,
			light));
}

t_error	scene_add_ambient_light(t_scene *scene, t_object *ambient_light)
{
	return (scene_add(
			scene->ambient_light,
			&(scene->ambient_light_size),
			SCENE_AMBIENT_LIGHTNING_LIMIT,
			ambient_light));
}

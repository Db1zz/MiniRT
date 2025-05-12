/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:38:01 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 14:38:01 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "vector.h" /* t_vector */
#include "scene.h" /* t_scene */
#include "utils.h" /* rt_calloc() */
#include "libft.h" /* ft_strcmp() */

#ifdef BONUS

void	parse_plane(t_scene *scene, char **line_data)
{
	t_plane		*plane;
	t_object	*object;
	t_aabb		box;

	if (scene->objects_size > SCENE_OBJECTS_LIMIT)
		return (set_error(
				&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));
	if (!check_amount_of_arguments(line_data, 5))
		return (set_error(&scene->error, ERR_ENTITY_ARGS, __func__));
	plane = rt_calloc(1, sizeof(t_plane), scene);
	if (!plane)
		return (set_error(&scene->error, ERR_MALLOC_FAILED, __func__));
	str_to_vector((&plane->pos), line_data[1], false, scene);
	str_to_vector(&plane->normal_vec, line_data[2], true, scene);
	str_to_color((&plane->color), line_data[3], scene);
	if (line_data[4] && !ft_strcmp(line_data[4], "1"))
		plane->check_board = true;
	else if (line_data[4])
		plane->texture = parse_texture(scene, line_data[4]);
	box = compute_plane_aabb();
	object = object_alloc(plane, box, E_PLANE, scene->objects_size);
	scene_add_object(scene, object);
	object->destructor = object_destroy_plane;
}

#endif // #ifdef BONUS
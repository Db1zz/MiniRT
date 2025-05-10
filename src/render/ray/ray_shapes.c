/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:28:24 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 02:28:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_shapes.h"

bool	ray_hit_shape(
	const t_ray *ray,
	const t_object *shape,
	t_hit_record *result_rec)
{
	static const t_ray_hit_shape_funp	arr[] = {
		ray_hit_sphere,
		ray_hit_cylinder,
		ray_hit_plane,
		ray_hit_gyper};

	return ((arr[(int)shape->type])(ray, shape, result_rec));
}

bool	ray_hit_multiple_shapes(
	const t_ray *ray,
	const t_object **shapes,
	t_hit_record *result_rec)
{
	int				i;
	bool			found;
	t_hit_record	current_rec;

	i = 0;
	found = false;
	init_hit_record(&current_rec);
	while (shapes[i])
	{
		if (ray_hit_shape(ray, shapes[i], &current_rec))
			found = true;
		if (found)
			*result_rec = *get_closest_hit(&current_rec, result_rec);
		++i;
	}
	return (found);
}

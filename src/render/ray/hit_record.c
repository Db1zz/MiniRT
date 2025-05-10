/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:21:56 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 02:21:56 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_record.h"

#include "minirt_math.h" /* FT_INFINITY */

void	init_hit_record(t_hit_record *rec)
{
	rec->color = (t_color){0, 0, 0};
	rec->front_face = false;
	rec->intersection_p = (t_vector){0, 0, 0};
	rec->normal = (t_vector){0, 0, 0};
	rec->ray_direction = (t_vector){0, 0, 0};
	rec->ray_distance = FT_INFINITY;
}

t_hit_record	*get_closest_hit(
	t_hit_record *first,
	t_hit_record *second)
{
	if (first->ray_distance > second->ray_distance)
		return (second);
	return (first);
}

t_vector	hit_record_to_ray_origin(const t_hit_record *rec)
{
	return (vec3_add_vec3(rec->intersection_p,
			vec3_mult(rec->normal, FT_EPSILON)));
}

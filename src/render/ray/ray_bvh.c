/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:24:44 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 02:24:44 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_bvh.h"

#include "ray_shapes.h" /* hit_aabb() */
#include "minirt_math.h" /* FT_EPSILON */

bool	ray_hit_bvh(
	const t_ray *ray,
	const t_bvh_node *tree,
	t_hit_record *rec,
	t_hit_record *temp)
{
	bool	left;
	bool	right;

	left = false;
	right = false;
	if (tree->objects)
	{
		if (ray_hit_shape(ray, tree->objects, temp))
		{
			*rec = *get_closest_hit(temp, rec);
			return (true);
		}
		return (false);
	}
	else if (ray_hit_aabb(ray, &tree->box))
	{
		left = ray_hit_bvh(ray, tree->left, rec, temp);
		right = ray_hit_bvh(ray, tree->right, rec, temp);
	}
	return (left || right);
}

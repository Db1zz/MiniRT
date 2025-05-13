/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_light.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:43:51 by gonische          #+#    #+#             */
/*   Updated: 2025/05/13 16:57:11 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_LIGHT_H
# define RAY_LIGHT_H

# include "ray.h" /* t_ray */
# include "hit_record.h" /* t_hit_record | functions */
# include "light.h" /* t_light */

t_ray	create_light_ray_from_hit(
			const t_hit_record *shape_rec,
			const t_light *light);

bool	light_ray_is_light_visible_in_bvh(
	const t_ray *light_ray,
	const t_bvh_node *tree,
	const t_hit_record *shape_rec,
	t_hit_record *result_rec);

bool	light_ray_is_light_visible_in_array(
			const t_ray *light_ray,
			const t_object **objects,
			t_hit_record *result_rec);

#endif // RAY_LIGHT_H

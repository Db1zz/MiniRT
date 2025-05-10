/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bvh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:52:10 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 00:52:10 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_BVH_H
# define RAY_BVH_H

# include "ray.h"

# include "hit_record.h" /* t_hit_record */
# include "bvh.h"		/* t_bvh_node */

bool	ray_hit_bvh(
			const t_ray *ray,
			const t_bvh_node *tree,
			t_hit_record *rec,
			t_hit_record *temp);

#endif // RAY_BVH_H
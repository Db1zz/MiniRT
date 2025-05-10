/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shapes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:55:38 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 00:55:38 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_SHAPES_H
# define RAY_SHAPES_H

# include "ray.h" /* ray | functions */
# include "hit_record.h" /* t_hit_record */

bool	ray_hit_shape(
			const t_ray *ray,
			const t_object *shape,
			t_hit_record *result_rec);

bool	ray_hit_aabb(
			const t_ray *r,
			const t_aabb *aabb);

bool	ray_hit_multiple_shapes(
			const t_ray *ray,
			const t_object **shapes,
			t_hit_record *result_rec);

bool	ray_hit_sphere(
			const t_ray *ray,
			const t_object *sphere_object,
			t_hit_record *rec);

bool	ray_hit_plane(
			const t_ray *ray,
			const t_object *plane_object,
			t_hit_record *rec);

bool	ray_hit_cylinder(
			const t_ray *ray,
			const t_object *cylinder_object,
			t_hit_record *rec);

bool	ray_hit_gyper(
			const t_ray *ray,
			const t_object *gyper,
			t_hit_record *rec);

#endif // RAY_SHAPES_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shapes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:55:38 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 16:56:54 by gwagner          ###   ########.fr       */
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

t_vector	calc_cylinder_normal(
	const t_cylinder *cy,
	const t_ray *ray,
	double *s2,
	double *dist);

bool	find_cylinder_solutions(
	const t_cylinder *cy,
	const t_ray *ray,
	double *s);

bool	tube_intersection(
	const t_cylinder *cy,
	const t_ray *ray,
	t_hit_record *rec);

#endif // RAY_SHAPES_H
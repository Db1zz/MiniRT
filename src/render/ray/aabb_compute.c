/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_compute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:26:54 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 02:26:54 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"

#include "object.h" /* t_cylinder | t_sphere */
#include "scene.h" /* macroses */
#include "vector.h" /* t_vector | functions */

#include <math.h> /* fmin() | fmax() */

t_aabb	compute_sphere_aabb(t_sphere *sphere)
{
	t_vector	vec;
	t_vector	a;
	t_vector	b;

	vec = create_vector(sphere->radius, sphere->radius, sphere->radius);
	a = vec3_sub_vec3(sphere->pos, vec);
	b = vec3_add_vec3(sphere->pos, vec);
	return (create_aabb_from_vectors(&a, &b));
}

t_aabb	compute_cylinder_aabb(t_cylinder *cylinder)
{
	t_vector	top_center;
	t_vector	bottom_center;
	t_vector	min_corner;
	t_vector	max_corner;
	t_vector	half_axis;

	half_axis = vec3_mult(cylinder->axis, cylinder->height);
	top_center = vec3_add_vec3(cylinder->pos, half_axis);
	bottom_center = cylinder->pos;
	min_corner.x = fmin(top_center.x, bottom_center.x) - cylinder->radius;
	min_corner.y = fmin(top_center.y, bottom_center.y) - cylinder->radius;
	min_corner.z = fmin(top_center.z, bottom_center.z) - cylinder->radius;
	max_corner.x = fmax(top_center.x, bottom_center.x) + cylinder->radius;
	max_corner.y = fmax(top_center.y, bottom_center.y) + cylinder->radius;
	max_corner.z = fmax(top_center.z, bottom_center.z) + cylinder->radius;
	return (create_aabb_from_vectors(&min_corner, &max_corner));
}

t_aabb	compute_plane_aabb(void)
{
	t_vector	min_corner;
	t_vector	max_corner;

	min_corner = create_vector(
			-SCENE_RENDER_DISTANCE,
			-SCENE_RENDER_DISTANCE,
			-SCENE_RENDER_DISTANCE);
	max_corner = create_vector(
			SCENE_RENDER_DISTANCE,
			SCENE_RENDER_DISTANCE,
			SCENE_RENDER_DISTANCE);
	return (create_aabb_from_vectors(&min_corner, &max_corner));
}

t_aabb	compute_hyperboloid_aabb(void)
{
	t_vector	min_corner;
	t_vector	max_corner;

	min_corner = create_vector(
			-SCENE_RENDER_DISTANCE,
			-SCENE_RENDER_DISTANCE,
			-SCENE_RENDER_DISTANCE);
	max_corner = create_vector(
			SCENE_RENDER_DISTANCE,
			SCENE_RENDER_DISTANCE,
			SCENE_RENDER_DISTANCE);
	return (create_aabb_from_vectors(&min_corner, &max_corner));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_math2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:53:17 by gwagner           #+#    #+#             */
/*   Updated: 2025/05/12 16:56:43 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector.h"
#include "ray_shapes.h" /* ray_hit_plane() */
#include "minirt_math.h" /* FT_EPSILON */

#define A 0
#define B 1
#define C 2

t_vector	calc_cylinder_normal(
	const t_cylinder *cy,
	const t_ray *ray,
	double *s2,
	double *dist)
{
	double	r_dist;
	double	s;
	bool	dist_valid[2];

	dist_valid[0] = dist[0] >= 0 && dist[0] <= cy->height && s2[0] > FT_EPSILON;
	dist_valid[1] = dist[1] >= 0 && dist[1] <= cy->height && s2[1] > FT_EPSILON;
	(set_double(&r_dist, dist[1]), set_double(&s, s2[1]));
	if (dist_valid[0] || dist_valid[1])
	{
		if (dist_valid[0] && dist_valid[1] && s2[0] < s2[1])
			(set_double(&r_dist, dist[0]), set_double(&s, s2[0]));
		else if (dist_valid[0] && !dist_valid[1])
			(set_double(&r_dist, dist[0]), set_double(&s, s2[0]));
	}
	s2[0] = s;
	return (vec3_normalize(vec3_sub_vec3(vec3_sub_vec3(vec3_mult(ray->direction,
						s), vec3_mult(cy->axis, r_dist)),
				vec3_sub_vec3(cy->pos, ray->origin))));
}

bool	find_cylinder_solutions(
	const t_cylinder *cy,
	const t_ray *ray,
	double *s)
{
	t_vector	v;
	t_vector	u;
	double		p[3];
	double		qp;

	v = vec3_mult(cy->axis, vec3_dot(ray->direction, cy->axis));
	v = vec3_sub_vec3(ray->direction, v);
	u = vec3_mult(cy->axis, vec3_dot(vec3_sub_vec3(ray->origin,
					cy->pos), cy->axis));
	u = vec3_sub_vec3(vec3_sub_vec3(ray->origin, cy->pos), u);
	p[A] = vec3_dot(v, v);
	p[B] = 2 * vec3_dot(v, u);
	p[C] = vec3_dot(u, u) - pow(cy->diameter / 2, 2);
	qp = sqrt(pow(p[B], 2) - 4 * p[A] * p[C]);
	s[0] = (-p[B] + qp) / (2 * p[A]);
	s[1] = (-p[B] - qp) / (2 * p[A]);
	if (s[0] != s[0] && s[1] != s[1])
		return (false);
	if (s[0] < FT_EPSILON && s[1] < FT_EPSILON)
		return (false);
	return (true);
}

static void	set_cylinder_hit_rec(
	const t_cylinder *cy,
	const t_ray *ray,
	const t_vector *normal,
	t_hit_record *rec)
{
	rec->color = cy->color;
	rec->ray_direction = ray->direction;
	rec->normal = *normal;
	rec->intersection_p = vec3_add_vec3(ray->origin,
			vec3_mult(ray->direction, rec->ray_distance));
}

static void	calc_tube_dist(
	const t_cylinder *cy,
	const t_ray *ray,
	double s2[2],
	double dist[2])
{
	dist[0] = vec3_dot(cy->axis, vec3_sub_vec3(
				vec3_mult(ray->direction, s2[0]),
				vec3_sub_vec3(cy->pos, ray->origin)));
	dist[1] = vec3_dot(cy->axis, vec3_sub_vec3(
				vec3_mult(ray->direction, s2[1]),
				vec3_sub_vec3(cy->pos, ray->origin)));
}

bool	tube_intersection(
	const t_cylinder *cy,
	const t_ray *ray,
	t_hit_record *rec)
{
	double		s2[2];
	double		dist[2];
	t_vector	normal;

	if (!find_cylinder_solutions(cy, ray, s2))
		return (false);
	calc_tube_dist(cy, ray, s2, dist);
	if (!((dist[0] >= 0 && dist[0] <= cy->height && s2[0] > FT_EPSILON)
			|| (dist[1] >= 0 && dist[1] <= cy->height && s2[1] > FT_EPSILON)))
		return (false);
	if (dist[0] >= 0 && dist[0] <= cy->height && s2[0] > FT_EPSILON
		&& !(dist[1] >= 0 && dist[1] <= cy->height && s2[1] > FT_EPSILON))
		s2[1] = s2[0];
	else if (dist[1] >= 0 && dist[1] <= cy->height && s2[1] > FT_EPSILON
		&& !(dist[0] >= 0 && dist[0] <= cy->height && s2[0] > FT_EPSILON))
		s2[0] = s2[1];
	normal = calc_cylinder_normal(cy, ray, s2, dist);
	if (s2[0] <= s2[1])
		rec->ray_distance = s2[0];
	else
		rec->ray_distance = s2[1];
	set_cylinder_hit_rec(cy, ray, &normal, rec);
	return (true);
}

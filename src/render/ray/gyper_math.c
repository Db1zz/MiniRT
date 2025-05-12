/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gyper_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:02:44 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 17:11:53 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

#include <stdlib.h> /* NULL */
#include <math.h> /* pow() | sqrt() | fmin() */

void	set_gyper_rec(
	t_gyper *hy,
	const t_ray *ray,
	t_hit_record *rec,
	double t)
{
	rec->intersection_p
		= vec3_add_vec3(ray->origin, vec3_mult(ray->direction, t));
	rec->ray_distance = t;
	rec->normal = vec3_normalize(create_vector(
				2 * rec->intersection_p.x / hy->squish.x,
				2 * rec->intersection_p.y / hy->squish.y,
				-2 * rec->intersection_p.z / hy->squish.z));
	rec->color = hy->color;
	rec->ray_direction = ray->direction;
}

static void	solve_t(const double *quad, double disc, double *t_result)
{
	double	t[2];

	t[0] = (-quad[1] + sqrt(disc)) / (2 * quad[0]);
	t[1] = (-quad[1] - sqrt(disc)) / (2 * quad[0]);
	if (t[0] < 0 && t[1] < 0)
	{
		*t_result = -1;
		return ;
	}
	if (t[0] < 0)
		t[0] = t[1];
	if (t[1] < 0)
		t[1] = t[0];
	*t_result = fmin(t[0], t[1]);
}

bool	gyper_intersection(
	t_gyper *hy,
	const t_ray *ray,
	t_hit_record *rec)
{
	double		quad[3];
	double		disc;
	double		t;
	t_vector	new_o;
	t_vector	param_sq;

	param_sq = create_vector(
			pow(hy->squish.x, 2), pow(hy->squish.y, 2), pow(hy->squish.z, 2));
	new_o = vec3_sub_vec3(ray->origin, hy->pos);
	quad[0] = (ray->direction.x * ray->direction.x / param_sq.x) * hy->axis.x
		+ (ray->direction.y * ray->direction.y / param_sq.y) * hy->axis.y
		+ (ray->direction.z * ray->direction.z / param_sq.z) * hy->axis.z;
	quad[1] = (2 * new_o.x * ray->direction.x / param_sq.x) * hy->axis.x
		+ (2 * ray->direction.y * new_o.y / param_sq.y) * hy->axis.y
		+ (2 * ray->direction.z * new_o.z / param_sq.z) * hy->axis.z;
	quad[2] = (pow(new_o.x, 2) / param_sq.x) * hy->axis.x
		+ (pow(new_o.y, 2) / param_sq.y) * hy->axis.y
		+ (pow(new_o.z, 2) / param_sq.z) * hy->axis.z - (hy->diameter / 2);
	disc = pow(quad[1], 2) - 4 * quad[0] * quad[2];
	if (disc < 0)
		return (false);
	if (solve_t(quad, disc, &t), t < 0)
		return (false);
	set_gyper_rec(hy, ray, rec, t);
	return (true);
}

bool	ray_hit_gyper(
	const t_ray *ray,
	const t_object *gyper,
	t_hit_record *rec)
{
	t_gyper	*hy;

	if (gyper->type != E_GYPER || gyper->data == NULL)
		return (false);
	hy = (t_gyper *)gyper->data;
	if (gyper_intersection(hy, ray, rec))
		return (true);
	return (false);
}

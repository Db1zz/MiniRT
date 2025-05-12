/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:56:46 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 14:56:46 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

#include "interval.h" /* t_interval */

#include "minirt_math.h" /* FT_INFINITY */

void	compare_t(double t0, double t1, t_interval *ray_t)
{
	if (t0 < t1)
	{
		if (t0 > ray_t->min)
			ray_t->min = t0;
		if (t1 < ray_t->max)
			ray_t->max = t1;
	}
	else
	{
		if (t1 > ray_t->min)
			ray_t->min = t1;
		if (t0 < ray_t->max)
			ray_t->max = t0;
	}
}

bool	ray_hit_aabb(const t_ray *r, const t_aabb *aabb)
{
	t_interval			ray_t;
	int					axis;
	double				t[2];
	double				adinv;
	const t_interval	*ax;

	ray_t = create_interval(0, FT_INFINITY);
	axis = 0;
	while (axis < 3)
	{
		ax = &aabb->interval[axis];
		adinv = 1.0 / ((double *)(&r->direction))[axis];
		t[0] = (ax->min - ((double *)(&r->origin))[axis]) * adinv;
		t[1] = (ax->max - ((double *)(&r->origin))[axis]) * adinv;
		compare_t(t[0], t[1], &ray_t);
		if (ray_t.max <= ray_t.min)
			return (false);
		++axis;
	}
	return (true);
}

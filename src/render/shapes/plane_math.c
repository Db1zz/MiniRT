/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:33 by gonische          #+#    #+#             */
/*   Updated: 2025/04/03 17:28:19 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include <math.h>

static void	set_plane_hit_rec(
	const t_plane *pl,
	const t_ray *ray,
	double dist,
	t_hit_record *rec)
{
	rec->ray_distance = dist;
	rec->intersection_p = vec3_add_vec3(ray->origin,
			vec3_mult(ray->direction, rec->ray_distance));
	rec->normal = vec3_normalize(pl->normal_vec);
	rec->obj_type = E_PLANE;
	rec->color = pl->color;
	rec->ray_direction = ray->direction;
}

bool	ray_hit_plane(
	const t_object *plane_object,
	const t_ray *ray,
	t_hit_record *rec)
{
	const double	epsilon = 1e-4;
	double			denom;
	double			t;
	t_plane			*plane;

	if (plane_object->type != E_PLANE || plane_object->data == NULL)
		return (false);
	plane = (t_plane *)plane_object->data;
	denom = vec3_dot(ray->direction, plane->normal_vec);
	if (fabs(denom) > epsilon)
	{
		t = vec3_dot(vec3_sub_vec3(plane->pos, ray->origin),
				plane->normal_vec) / denom;
		if (t >= 0)
		{
			if (denom > epsilon)
				rec->front_face = true;
			set_plane_hit_rec(plane, ray, t, rec);
			return (true);
		}
	}
	return (false);
}

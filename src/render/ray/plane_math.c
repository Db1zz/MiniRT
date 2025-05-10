/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:33 by gonische          #+#    #+#             */
/*   Updated: 2025/05/07 18:54:07 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

#include "ray.h" /* t_ray */
#include "ray_texture.h" /* get_plane_color() */
#include "minirt_math.h" /* FT_EPSILON */

#include <math.h> /* fabs() */

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
	if (pl->texture || pl->check_board)
		rec->color = get_plane_color(pl, rec);
	else
		rec->color = pl->color;
	rec->ray_direction = ray->direction;
}

bool	ray_hit_plane(
	const t_ray *ray,
	const t_object *plane_object,
	t_hit_record *rec)
{
	double		denom;
	double		t;
	t_plane		*plane;

	if (plane_object->type != E_PLANE || plane_object->data == NULL)
		return (false);
	plane = (t_plane *)plane_object->data;
	denom = vec3_dot(ray->direction, plane->normal_vec);
	if (fabs(denom) > FT_EPSILON)
	{
		t = vec3_dot(vec3_sub_vec3(plane->pos, ray->origin),
				plane->normal_vec) / denom;
		if (t >= 0)
		{
			if (denom > FT_EPSILON)
				rec->front_face = true;
			set_plane_hit_rec(plane, ray, t, rec);
			return (true);
		}
	}
	return (false);
}

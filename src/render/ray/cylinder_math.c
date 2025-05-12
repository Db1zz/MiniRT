/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:43:28 by gwagner           #+#    #+#             */
/*   Updated: 2025/05/12 16:56:16 by gwagner          ###   ########.fr       */
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

void	set_double(double *var, double val)
{
	if (!var)
		return ;
	*var = val;
}

bool	check_hits(
	const t_cylinder *cy,
	t_hit_record cap_rec[2],
	t_hit_record *rec,
	bool hit[2]
)
{
	t_vector	p2;

	p2 = ((const t_plane *)(cy->caps[1].data))->pos;
	if ((hit[0] && vec3_distance(cap_rec[0].intersection_p,
				cy->pos) <= cy->diameter / 2) && (hit[1]
			&& vec3_distance(cap_rec[1].intersection_p, p2)
			<= cy->diameter / 2))
	{
		if (cap_rec[0].ray_distance < cap_rec[1].ray_distance)
			*rec = cap_rec[0];
		else
			*rec = cap_rec[1];
		return (true);
	}
	else if (hit[1] && vec3_distance(cap_rec[1].intersection_p, p2)
		<= cy->diameter / 2)
	{
		*rec = cap_rec[1];
		return (true);
	}
	return (false);
}

static bool	caps_intersection(
	const t_cylinder *cy,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_hit_record	cap_rec[2];
	bool			hit[2];

	init_hit_record(&cap_rec[0]);
	init_hit_record(&cap_rec[1]);
	hit[0] = ray_hit_plane(ray, (const t_object *)&(cy->caps[0]), &cap_rec[0]);
	hit[1] = ray_hit_plane(ray, (const t_object *)&(cy->caps[1]), &cap_rec[1]);
	if ((hit[0] || hit[1]) && check_hits(cy, cap_rec, rec, hit))
		return (true);
	else if (hit[0] && vec3_distance(cap_rec[0].intersection_p, cy->pos)
		<= cy->diameter / 2)
	{
		*rec = cap_rec[0];
		return (true);
	}
	return (false);
}

void	set_rec_cy(
	t_hit_record *rec,
	t_hit_record cyl,
	t_hit_record cap,
	bool hit[2]
	)
{
	if (hit[0] && hit[1])
	{
		if (cyl.ray_distance < cap.ray_distance)
			*rec = cyl;
		else
			*rec = cap;
	}
	else if (hit[0])
		*rec = cyl;
	else if (hit[1])
		*rec = cap;
}

bool	ray_hit_cylinder(
	const t_ray *ray,
	const t_object *cylinder_object,
	t_hit_record *rec)
{
	t_cylinder		*cylinder;
	t_hit_record	cylinder_rec;
	t_hit_record	cap_rec;
	bool			hit[2];

	if (!cylinder_object || cylinder_object->type != E_CYLINDER)
		return (false);
	cylinder = cylinder_object->data;
	init_hit_record(&cylinder_rec);
	init_hit_record(&cap_rec);
	hit[0] = tube_intersection(cylinder, ray, &cylinder_rec);
	hit[1] = caps_intersection(cylinder, ray, &cap_rec);
	set_rec_cy(rec, cylinder_rec, cap_rec, hit);
	if (hit[0] || hit[1])
		return (true);
	return (false);
}

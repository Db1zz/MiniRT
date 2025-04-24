/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:28 by gonische          #+#    #+#             */
/*   Updated: 2025/04/13 17:32:47 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt_math.h"
#include "interval.h"
#include <math.h>

static void ray_hit_record_set_face_normal(
	const t_ray *ray,
	const t_vector *outward_normal,
	t_hit_record *rec)
{
	rec->front_face = vec3_dot(ray->direction, *outward_normal) < 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = vec3_mult(*outward_normal, -1);
	rec->normal = vec3_normalize(rec->normal);
}

static double sphere_solve_qf(
	double discriminant,
	double qf[3],
	const t_interval *interval)
{
	double root;
	double sqrtd;

	sqrtd = sqrt(discriminant);
	root = (qf[1] - sqrtd) / qf[0];
	if (!interval_contains(root, interval))
	{
		root = (qf[1] + sqrtd) / qf[0];
		if (!interval_contains(root, interval))
			return (-1.0);
	}
	return (root);
}

static bool sphere_find_solutions(
	const t_sphere *sphere,
	const t_ray *ray,
	const t_interval *interval,
	t_hit_record *rec)
{
	t_vector oc;
	double qf[3];
	double discriminant;

	oc = vec3_sub_vec3(sphere->pos, ray->origin);
	qf[0] = vec3_length_squared(ray->direction);
	qf[1] = vec3_dot(ray->direction, oc);
	qf[2] = vec3_length_squared(oc) - sphere->radius * sphere->radius;
	discriminant = qf[1] * qf[1] - qf[0] * qf[2];
	if (discriminant >= 0)
		rec->ray_distance = sphere_solve_qf(discriminant, qf, interval);
	else
		return (false);
	rec->intersection_p = vec3_add_vec3(ray->origin,
										vec3_mult(ray->direction, rec->ray_distance));
	return (rec->ray_distance >= 0);
}

bool ray_hit_sphere(
		const t_ray *ray,
		const t_object *sphere_object,
		t_hit_record *rec)
{
	const t_interval interval = create_interval(0.01, FT_INFINITY);
	t_vector outward_normal;
	t_sphere *sphere;

	if (sphere_object->type != E_SPHERE || sphere_object->data == NULL)
		return (false);
	sphere = (t_sphere *)sphere_object->data;
	if (!sphere_find_solutions(sphere, ray, &interval, rec))
		return (false);
	outward_normal = vec3_div(
		vec3_sub_vec3(rec->intersection_p, sphere->pos), sphere->radius);
	ray_hit_record_set_face_normal(ray, &outward_normal, rec);
	rec->color = sphere->color;
	rec->ray_direction = ray->direction;
	return (true);
}

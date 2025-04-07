#include "minirt.h"
#include "ray.h"
#include "vector.h"

#ifndef EPSILON
#define EPSILON 1e-4
#endif  // EPSILON

#define A 0
#define B 1
#define C 2

static bool find_cylinder_solutions(
	const t_cylinder *cy,
	const t_ray *ray,
	double *s)
{
	t_vector v;
	t_vector u;
	double p[3];
	double qp;

	v = vec3_mult(cy->axis, vec3_dot(ray->direction, cy->axis));
	v = vec3_sub_vec3(ray->direction, v);
	u = vec3_mult(cy->axis, vec3_dot(vec3_sub_vec3(ray->origin, cy->pos), cy->axis));
	u = vec3_sub_vec3(vec3_sub_vec3(ray->origin, cy->pos), u);
	p[A] = vec3_dot(v, v);
	p[B] = 2 * vec3_dot(v, u);
	p[C] = vec3_dot(u, u) - pow(cy->diameter / 2, 2);
	qp = sqrt(pow(p[B], 2) - 4 * p[A] * p[C]);
	s[0] = (-p[B] + qp) / (2 * p[A]);
	s[1] = (-p[B] - qp) / (2 * p[A]);
	if (s[0] != s[0] && s[1] != s[1])
		return (false);
	if (s[0] < EPSILON && s[1] < EPSILON)
		return (false);
	return (true);
}

void set_double(double *var, double val) {
	if (!var)
		return;
	*var = val;
}

static t_vector calc_cylinder_normal(
	const t_cylinder *cy,
	const t_ray *ray,
	double *s2,
	double *dist)
{
	double r_dist;
	double s;
	bool dist_valid[2];

	dist_valid[0] = dist[0] >= 0 && dist[0] <= cy->height && s2[0] > EPSILON;
	dist_valid[1] = dist[1] >= 0  && dist[1] <= cy->height && s2[1] > EPSILON;
	(set_double(&r_dist, dist[1]), set_double(&s, s2[1]));
	if (dist_valid[0] || dist_valid[1])
	{
		if(dist_valid[0] && dist_valid[1] && s2[0] < s2[1])
			(set_double(&r_dist, dist[0]), set_double(&s, s2[0]));
		else if (dist_valid[0] && !dist_valid[1])
			(set_double(&r_dist, dist[0]), set_double(&s, s2[0]));
	}
	s2[0] = s;
	return (vec3_normalize(vec3_sub_vec3(vec3_sub_vec3(vec3_mult(ray->direction, s), vec3_mult(cy->axis, r_dist)), vec3_sub_vec3(cy->pos, ray->origin))));
}

static void set_cylinder_hit_rec(
	const t_cylinder *cy,
	const t_ray *ray,
	const t_vector *normal,
	double distance,
	t_hit_record *rec)
{
	rec->color = cy->color;
	rec->obj_type = E_CYLINDER;
	rec->ray_distance = distance;
	rec->ray_direction = ray->direction;
	rec->normal = *normal;
	rec->intersection_p = vec3_add_vec3(ray->origin,
					vec3_mult(ray->direction, rec->ray_distance));
}

static bool tube_intersection(
	const t_cylinder *cy,
	const t_ray *ray,
	t_hit_record *rec)
{
	double s2[2];
	double dist[2];
	t_vector normal;

	if (!find_cylinder_solutions(cy, ray, s2))
		return false;

	dist[0] = vec3_dot(cy->axis, vec3_sub_vec3(
			vec3_mult(ray->direction, s2[0]),
			vec3_sub_vec3(cy->pos, ray->origin)));
	dist[1] = vec3_dot(cy->axis, vec3_sub_vec3(
			vec3_mult(ray->direction, s2[1]),
			vec3_sub_vec3(cy->pos, ray->origin)));

	if (!((dist[0] >= 0 && dist[0] <= cy->height && s2[0] > EPSILON)
		|| (dist[1] >= 0 && dist[1] <= cy->height && s2[1] > EPSILON)))
		return (false);
	if (dist[0] >= 0 && dist[0] <= cy->height && s2[0] > EPSILON
		&& !(dist[1] >= 0 && dist[1] <= cy->height && s2[1] > EPSILON))
		s2[1] = s2[0];
	else if (dist[1] >= 0 && dist[1] <= cy->height && s2[1] > EPSILON && !(dist[0] >= 0 && dist[0] <= cy->height && s2[0] > EPSILON))
		s2[0] = s2[1];
	normal = calc_cylinder_normal(cy, ray, s2, dist);
	set_cylinder_hit_rec(cy, ray, &normal, s2[0] < s2[1] ? s2[0] : s2[1], rec);
	return (true);
}

static t_object	*init_caps(
		const t_cylinder *cy,
		t_vector *p2
	)
{
	t_plane			*cap_plane;
	t_object	*cap;

	cap_plane = malloc(sizeof(t_plane) * 2);
	*p2 = vec3_add_vec3(cy->pos, vec3_mult(cy->axis, cy->height));
	cap_plane[0].pos = vec3_mult(cy->pos, 1);
	cap_plane[0].normal_vec = vec3_mult(cy->axis, -1);
	cap_plane[0].color = cy->color;
	cap_plane[1].pos = *p2;
	cap_plane[1].normal_vec = cy->axis;
	cap_plane[1].color = cy->color;
	cap = alloc_new_object(&cap_plane[0], E_PLANE, NULL);
	cap->next = alloc_new_object(&cap_plane[1], E_PLANE, NULL);
	return (cap);
}

static free_caps(t_object **cap)
{
	free((*cap)->data);
	free((*cap)->next);
	free(*cap);
}

static bool	caps_intersection(
	const t_cylinder *cy,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_vector		p2;
	t_hit_record	cap_rec[2];
	t_object	*cap;
	bool			hit[2];

	init_hit_record(&cap_rec[0]);
	init_hit_record(&cap_rec[1]);
	cap = init_caps(cy, &p2);
	hit[0] = ray_hit_plane(cap, ray, &cap_rec[0]);
	hit[1] = ray_hit_plane(cap->next, ray, &cap_rec[1]);
	free_caps(&cap);
	if (hit[0] || hit[1])
	{
		if ((hit[0] 
			&& vec3_distance(cap_rec[0].intersection_p, cy->pos) <= cy->diameter / 2)
			&& (hit[1] && vec3_distance(cap_rec[1].intersection_p, p2) <= cy->diameter / 2))
		{
			if (cap_rec[0].ray_distance < cap_rec[1].ray_distance)
				*rec = cap_rec[0];
			else
				*rec = cap_rec[1];
			return (true);
		}
		else if (hit[0] 
			&& vec3_distance(cap_rec[0].intersection_p, cy->pos) <= cy->diameter / 2)
		{
			*rec = cap_rec[0];
			return (true);
		}
		else if (hit[1] && vec3_distance(cap_rec[1].intersection_p, p2) <= cy->diameter / 2)
		{
			*rec = cap_rec[1];
			return (true);
		}
		return (false);
	}
	return (false);
}

bool ray_hit_cylinder(
	const t_object *cylinder_object,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_cylinder		*cylinder;
	t_hit_record 	cylinder_rec;
	t_hit_record 	cap_rec;
	bool			hit[2];

	if (!cylinder_object || cylinder_object->type != E_CYLINDER)
		return (false);
	cylinder = cylinder_object->data;
	init_hit_record(&cylinder_rec);
	init_hit_record(&cap_rec);
	hit[0] = tube_intersection(cylinder, ray, &cylinder_rec);
	hit[1] = caps_intersection(cylinder, ray, &cap_rec);
	if (hit[0] && hit[1])
	{
		if (cylinder_rec.ray_distance < cap_rec.ray_distance)
			*rec = cylinder_rec;
		else
			*rec = cap_rec;
	}
	else if (hit[0])
		*rec = cylinder_rec;
	else if (hit[1])
		*rec = cap_rec;
	if (hit[0] || hit[1])
		return (true);
	return (false);
}

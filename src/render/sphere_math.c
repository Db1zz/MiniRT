#include "ray.h"
#include "minirt_math.h"
#include <math.h>

static double	sphere_solve_qf(double discriminant, double qf[3],
			const t_interval *interval)
{
	double	root;
	double	sqrtd;

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

static bool	sphere_find_solutions(const t_sphere *sphere, const t_ray *ray,
			const t_interval *interval, t_hit_record *rec)
{
	t_vector	oc;
	double		qf[3]; // a[0] h[1] c[2]
	double		discriminant;

	oc = vec3_sub_vec3(sphere->vector, ray->origin);
	qf[0] = vec3_lenght_squared(&ray->direction);
	qf[1] = vec3_dot(ray->direction, oc);
	qf[2] = vec3_lenght_squared(&oc) - sphere->radius * sphere->radius;
	discriminant = qf[1] * qf[1] - qf[0] * qf[2];
	if (discriminant >= 0)
		rec->t = sphere_solve_qf(discriminant, qf, interval);
	else
		return (false);
	rec->p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, discriminant));
	return (rec->t >= 0);
}

bool	ray_hit_sphere(const t_object_list *sphere_object, const t_ray *ray,
			const t_interval *interval, t_hit_record *rec)
{
	t_vector	outward_normal;
	t_sphere	*sphere;

	if (sphere_object->type != E_SPHERE || sphere_object->data == NULL)
		return (false);
	sphere = (t_sphere *)sphere_object->data;
	if (!sphere_find_solutions(sphere, ray, interval, rec))
		return (false);
	outward_normal = vec3_div(vec3_sub_vec3(rec->p, sphere->vector), sphere->radius);
	ray_hit_record_set_face_normal(ray, &outward_normal, rec);
	rec->color = sphere->color;
	return (true);
}

#include "camera.h"
#include "shapes.h"
#include "minirt_math.h"
#include <math.h>

static double	sphere_solve_qf(double discriminant, double qf[3],
		double t_min, double t_max)
{
	double	root;
	double	sqrtd;

	sqrtd = sqrt(discriminant);
	root = (qf[1] - sqrtd) / qf[0];
	if (!interval_contains(root, t_min, t_max))
	{
		root = (qf[1] + sqrtd) / qf[0];
		if (!interval_contains(root, t_min, t_max))
			return (-1.0);
	}
	return (root);
}

bool	ray_hit_sphere(const t_sphere *sphere, const t_ray *ray,
			double ray_t_min_max[2], t_hit_record *rec)
{
	t_vector	oc;
	double		qf[3]; // a[0] h[1] c[2]
	double		disc;
	t_vector	outward_normal;

	while (sphere)
	{
		oc = vec3_sub_vec3(sphere->vector, ray->origin);
		qf[0] = vec3_lenght_squared(&ray->direction);
		qf[1] = vec3_dot(ray->direction, oc);
		qf[2] = vec3_lenght_squared(&oc) - sphere->radius * sphere->radius;
		disc = qf[1] * qf[1] - qf[0] * qf[2];
		rec->t = sphere_solve_qf(disc, qf, ray_t_min_max[0], ray_t_min_max[1]);
		if (disc < 0 || rec->t < 0)
		{
			sphere = sphere->next;
			continue ;
		}
		rec->p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, disc));
		outward_normal = vec3_div(vec3_sub_vec3(rec->p, sphere->vector), sphere->radius);
		hit_record_set_face_normal(ray, &outward_normal, rec);
		sphere = sphere->next;
		return (true);
	}
	return (false);
}

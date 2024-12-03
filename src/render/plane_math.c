#include "minirt.h"

double	fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

bool	ray_hit_plane(t_ray ray, t_plane plane)
{
	double denom;
	double t;

	denom = vec3_dot(ray.dir, plane.normal);
	if (fabs(denom) > 0.0001)
	{
		t = vec3_dot(vec3_sub_vec3(plane.point, ray.origin), plane.normal) / denom;
		if (t >= 0)
			return (true);
	}
	return (false);
}
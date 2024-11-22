#include "camera.h"
#include "shapes.h"
#include <math.h>

double	ray_hit_sphere(const t_sphere *spheres, const t_ray *ray)
{
	t_vector	oc;
	double		a;
	double		h;
	double		c;
	double		discriminant;

	while (spheres)
	{
		oc = vec3_sub_vec3(spheres->vector, ray->origin);
		a = vec3_lenght_squared(&ray->direction);
		h = vec3_dot(ray->direction, oc);
		c = vec3_lenght_squared(&oc) - spheres->radius * spheres->radius;
		discriminant = h * h - a * c;
		if (discriminant >= 0.0)
			return ((h - sqrt(discriminant)) / a);
		spheres = spheres->next;
	}
	return (-1.0);
}
#include "minirt.h"

double	fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

bool	ray_hit_plane(t_ray ray, t_object_list *plane_object, t_hit_record *rec)
{
	double denom;
	double t;
    t_plane *plane;

    if (plane_object->type != E_PLANE || plane_object->data == NULL)
		return (false);
    plane = (t_plane *)plane_object->data;
	denom = vec3_dot(ray.direction, plane->vector);
	if (fabs(denom) > 0.0001)
	{
		t = vec3_dot(vec3_sub_vec3(plane->point, ray.origin), plane->vector) / denom;
		if (t >= 0)
        {
            if (denom > 0.0001) {
                rec->front_face = true;
            }
            rec->t = t;
            rec->normal = plane->vector;
            rec->obj_type = E_PLANE;
			return (true);
        }
	}
	return (false);
}
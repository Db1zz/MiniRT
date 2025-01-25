#include "minirt.h"
#include "ray.h"

double	fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

bool	ray_hit_plane(
	const t_object_list	*plane_object,
	const t_ray			*ray,
	t_hit_record		*rec)
{
	const double	epsilon = 1e-4;
	double 			denom;
	double 			t;
    t_plane 		*plane;

    if (plane_object->type != E_PLANE || plane_object->data == NULL)
		return (false);
    plane = (t_plane *)plane_object->data;
	denom = vec3_dot(ray->direction, plane->normal_vec);
	if (fabs(denom) > epsilon)
	{
		t = vec3_dot(vec3_sub_vec3(plane->pos, ray->origin), plane->normal_vec) / denom;
		if (t >= 0)
        {
            if (denom > epsilon)
                rec->front_face = true;
			rec->ray_distance = t;
			rec->intersection_p = vec3_add_vec3(ray->origin,
					vec3_mult(ray->direction, rec->ray_distance));
			rec->normal = vec3_normalize(plane->normal_vec);
			rec->obj_type = E_PLANE;
			rec->color = plane->color;
			rec->ray_direction = ray->direction;
			return (true);
        }
	}
	return (false);
}

#include "ray.h"
#include <stdio.h>

bool	ray_hit_light(const t_object_list *objects, const t_ray *shadow_ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	t_light	*light;
	double	light_intersect;

	light = (t_light *)prop->light->data;
	t_vector	vec = vec3_sub_vec3(light->vector, shadow_ray->origin);
	light_intersect = vec3_lenght(&vec);
	if (ray_hit(objects, shadow_ray, prop, rec))
		return (light_intersect <= rec->t - 1e-4);
	return (true);
}

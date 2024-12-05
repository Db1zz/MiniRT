#include "ray.h"
#include "light.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	return ((t_ray){origin, direction, (t_color){0, 0, 0}});
}

bool	ray_hit(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	bool			found;

	found = false;
	while (objects)
	{
		if (ray_hit_sphere(objects, ray, &prop->ray_interval, &temp_rec)
				&& temp_rec.t < rec->t)
		{
			rec->t = temp_rec.t;
			rec->normal = temp_rec.normal;
			rec->front_face = temp_rec.front_face;
			rec->obj_type = temp_rec.obj_type;
			rec->p = temp_rec.p;
			rec->color = temp_rec.color;
			found = true;
		}
		objects = objects->next;
	}
	return (found);
}

t_color	process_ray_hit(const t_object_list *objects,
			const t_ray_properties *prop, const t_hit_record *rec)
{
	t_color			ray_color;
	double			light_intensity;

	light_intensity = send_shadow_ray(objects, prop, rec);
	ray_color = clr_mult(rec->color, light_intensity);
	return (ray_color);
}

t_color	ray_send(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	if (prop->max_diffusion_depth > 0 && ray_hit(objects, ray, prop, rec))
		return (process_ray_hit(objects, prop, rec));
	return (ray_get_background_color(ray));
}

#include "minirt_math.h"
t_color	ray_color(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop)
{
	t_hit_record		rec;
	t_ray_properties	prop_copy;

	prop_copy = *prop;
	rec.t = FT_INFINITY;
	return (ray_send(objects, ray, &prop_copy, &rec));
}

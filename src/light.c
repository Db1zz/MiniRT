#include "minirt.h"
#include "light.h"
#include "ray.h"
#include "math.h"
#include "minirt_math.h"

t_color	get_diffuse_light(
	const t_object_list		*objects,
	const t_ray_properties	*prop,
	const t_hit_record		*shape_rec)
{
	t_object_list	*light_sources;
	t_light			*light;
	t_ray			shadow_ray;
	t_hit_record	shadow_ray_rec;
	t_color			result_color;

	light_sources = prop->light;
	result_color = create_color(0,0,0);
	while (light_sources)
	{
		light = light_sources->data;
		init_hit_record(&shadow_ray_rec);
		shadow_ray = calculate_create_shadow_ray(shape_rec, light);
		if (ray_hit_light(objects, &shadow_ray, prop, &shadow_ray_rec))
		{
			result_color = clr_add_clr(
				clr_mult(
					filter_color(shape_rec->color, light->color),
					get_diffuse_intensity(light, shape_rec)), result_color);
		}
		light_sources = light_sources->next;
	}
	return (result_color);
}

t_color	get_specular_light(
	const t_ray_properties	*prop,
	const t_hit_record		*hit_rec,
	const t_ray				*camera_ray)
{
	double			specular;
	t_object_list	*light_sources;
	t_light			*light;
	t_color			result_color;

	light_sources = prop->light;
	result_color = create_color(0,0,0);
	while (light_sources)
	{
		light = light_sources->data;
		specular = calculate_specular_light(light, camera_ray, hit_rec, 1);
		result_color = clr_add_clr(result_color, clr_mult(light->color, specular));
		light_sources = light_sources->next;
	}
	result_color = normalize_color(result_color);
	return (result_color);
}

t_color	get_ambient_light(
	const t_object_list	*amb_object,
	const t_color		*color)
{
	const t_amb_lighting	*amb_light;
	t_color					amb_color;

	amb_light = (const t_amb_lighting *)amb_object->data;
	amb_color = clr_mult(amb_light->color, amb_light->ratio);
	return (normalize_color(clr_add_clr(*color, amb_color)));
}

t_color	apply_light(
	const t_object_list		*objects,
	const t_ray				*camera_ray,
	const t_ray_properties	*prop,
	const t_hit_record		*rec)
{
	t_color	result;

	result = create_color(0,0,0);
	if (prop->light)
		result = get_diffuse_light(objects, prop, rec);
	if (prop->amb_lighting)
		result = get_ambient_light(prop->amb_lighting, &result);
	result = clr_add_clr(result, get_specular_light(prop, rec, camera_ray));
	return (result);
}

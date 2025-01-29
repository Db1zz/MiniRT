#include "minirt.h"
#include "light.h"
#include "ray.h"
#include "math.h"
#include "minirt_math.h"

static t_color	get_diffuse_light(
	const t_scene		*scene,
	const t_hit_record	*shape_rec)
{
	t_object_list	*light_sources;
	t_light			*light;
	t_ray			light_ray;
	t_hit_record	light_ray_rec;
	t_color			result_color;

	light_sources = scene->lights;
	result_color = create_color(0,0,0);
	while (light_sources)
	{
		light = light_sources->data;
		init_hit_record(&light_ray_rec);
		light_ray = create_light_ray(shape_rec, light);
		if (ray_hit_light(&light_ray, scene->objects, &light_ray_rec))
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

static t_color	get_specular_light(
	const t_ray			*camera_ray,
	const t_scene		*scene,
	const t_hit_record	*hit_rec)
{
	double			specular;
	t_object_list	*light_sources;
	t_light			*light;
	t_color			result_color;

	light_sources = scene->lights;
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

static t_color	get_ambient_light(
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
	const t_ray			*camera_ray,
	const t_scene		*scene,
	const t_hit_record	*shape_rec)
{
	t_color	result;

	result = create_color(0,0,0);
	if (scene->lights)
		result = get_diffuse_light(scene, shape_rec);
	if (scene->ambient_lightings)
		result = get_ambient_light(scene->ambient_lightings, &result);
	result = clr_add_clr(result, get_specular_light(camera_ray, scene, shape_rec));
	return (result);
}

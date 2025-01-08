#include "light.h"
#include "ray.h"
#include "math.h"
#include "minirt_math.h"

double	calculate_specular_light(
	const t_light		*light,
	const t_ray			*camera_ray,
	const t_hit_record	*hit_rec,
	double				specular_reflection_coefficient)
{
	t_vector		halfway_vector;
	t_vector		light_dir;
	t_vector		view_dir;
	double	dot;
	double	specular;

	light_dir = get_ray_direction(light->pos, hit_rec->intersection_p);
	view_dir = get_ray_direction(camera_ray->origin, hit_rec->intersection_p);
	halfway_vector = vec3_normalize(vec3_add_vec3(light_dir, view_dir));
	dot = vec3_dot(hit_rec->normal, halfway_vector);
	specular = pow(dot, 50);
	return (specular * light->ratio * specular_reflection_coefficient);
}

bool	ray_hit_light(
	const t_object_list		*objects,
	const t_ray				*shadow_ray,
	const t_ray_properties	*prop,
	t_hit_record			*rec)
{
	const double	EPSILON = 1e-4;
	t_light			*light;
	double			light_intersect;

	light = (t_light *)prop->light->data;
	light_intersect = vec3_lenght(&shadow_ray->direction);
	if (ray_hit(objects, shadow_ray, prop, rec))
		return (light_intersect <= rec->ray_distance - EPSILON);
	return (true);
}

double	get_diffuse_intensity(
	const t_light		*light_source,
	const t_hit_record	*shape_rec)
{
	t_vector	cos;
	t_vector	sin;
	double		diffuse_intensity;

	cos = vec3_normalize(
			vec3_sub_vec3(light_source->pos, shape_rec->intersection_p));
	sin = vec3_normalize(shape_rec->normal);
	diffuse_intensity = vec3_dot(cos, sin);
	diffuse_intensity = fmax(0, diffuse_intensity) * light_source->ratio;
	return (diffuse_intensity);
}

t_ray	calculate_create_shadow_ray(
	const t_hit_record	*shape_rec,
	const t_light		*light)
{
	t_vector	ray_origin;
	t_vector	ray_direction;
	t_ray		new_shadow_ray;

	ray_origin = hit_record_to_ray_origin(shape_rec);
	ray_direction = vec3_sub_vec3(light->pos, ray_origin);
	new_shadow_ray = create_ray(ray_origin, ray_direction, create_color(0,0,0));
	return (new_shadow_ray);
}

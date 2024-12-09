# include "light.h"
# include "ray.h"
# include "math.h"

bool	ray_hit_light(const t_object_list *objects, const t_ray *shadow_ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	const double	epsilon = 1e-4;
	t_light			*light;
	double			light_intersect;

	light = (t_light *)prop->light->data;
	light_intersect = vec3_lenght(&shadow_ray->direction);
	if (ray_hit(objects, shadow_ray, prop, rec))
		return (light_intersect <= rec->t - epsilon);
	return (true);
}

t_color	apply_ambient_light(const t_object_list *amb_object, const t_color *color)
{
	const t_amb_lighting	*amb_light;
	t_color					amb_color;

	if (!amb_object || !amb_object->data
		|| amb_object->type != E_AMBIENT_LIGHT || !color)
	{
		ft_perror(ERR_INVALID_FUNC_ARGS, __func__);
		return ((t_color){0, 0, 0});
	}
	amb_light = (const t_amb_lighting *)amb_object->data;
	amb_color = clr_mult(amb_light->color, amb_light->ratio);
	return (normalize_color(clr_add_clr(*color, amb_color)));
}

static t_ray	calculate_create_shadow_ray(
			const t_hit_record *shape_rec, const t_light *light)
{
	const double	epsilon = 1e-4;
	t_vector		ray_intersection;
	t_vector		ray_direction;
	t_ray			new_shadow_ray;

	ray_intersection = vec3_add_vec3(shape_rec->p,
				vec3_mult(shape_rec->normal, epsilon));
	ray_direction = vec3_sub_vec3(light->vector, ray_intersection);
	new_shadow_ray = create_ray(ray_intersection, ray_direction);
	return (new_shadow_ray);
}

/*
	TODO: Refactor this function ;)
*/
double	send_shadow_ray(const t_object_list *objects,
			const t_ray_properties *prop, const t_hit_record *shape_rec)
{
	t_light			*light_source;
	t_ray			shadow_ray;
	t_hit_record	shadow_ray_rec;
	double			diffuse_intensity;
	t_vector		cossin_angle_vectors[2];

	if (!prop || !prop->light || prop->light->type != E_LIGHT
		|| !objects || !shape_rec)
		return (ft_perror(ERR_INVALID_FUNC_ARGS, __func__), 0);
	light_source = prop->light->data;
	shadow_ray = calculate_create_shadow_ray(shape_rec, light_source);
	init_hit_record(&shadow_ray_rec);
	if (!ray_hit_light(objects, &shadow_ray, prop, &shadow_ray_rec))
		return (0);
	cossin_angle_vectors[0] = vec3_normalize(vec3_sub_vec3(light_source->vector, shape_rec->p));
	cossin_angle_vectors[1] = vec3_normalize(shape_rec->normal);
	diffuse_intensity = vec3_dot(cossin_angle_vectors[0], cossin_angle_vectors[1]);
	return (fmax(0, diffuse_intensity));
}

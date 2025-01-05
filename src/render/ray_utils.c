#include "ray.h"
#include "minirt_math.h"

void	init_hit_record(t_hit_record *rec)
{
	ft_memset(rec, 0, sizeof(t_hit_record));
	rec->ray_distance = FT_INFINITY;
}

t_hit_record	get_closest_hit(
	const t_hit_record	*first,
	const t_hit_record	*second)
{
	if (first->ray_distance > second->ray_distance)
		return (*second);
	return (*first);
}

t_vector	hit_record_to_ray_origin(const t_hit_record *rec)
{
	const double	EPSILON = 1e-4;
	t_vector		origin;

	origin = 
			vec3_add_vec3(rec->intersection_p, vec3_mult(rec->normal, EPSILON));
	return (origin);
}

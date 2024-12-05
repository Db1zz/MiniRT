#include "ray.h"
#include "minirt_math.h"

void	init_hit_record(t_hit_record *rec)
{
	ft_memset(rec, 0, sizeof(t_hit_record));
	rec->t = FT_INFINITY;
}

t_hit_record	get_closest_hit(const t_hit_record *first,
			const t_hit_record *second)
{
	if (first->t > second->t)
		return (*second);
	return (*first);
}

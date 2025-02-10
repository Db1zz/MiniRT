#include "minirt.h"

bool	ray_hit_cone_body(t_cone *cone, const t_ray *ray, t_hit_record *rec)
{

}

bool	ray_hit_cone(const t_object_list *objects, const t_ray *ray, t_hit_record *rec)
{
	t_cone			*cone;
	t_hit_record		body;

	if (objects->type != E_CONE || objects->data == NULL)
		return (false);
	cone = (t_cone *)cylinder_object->data;
	init_hit_record(&body);
	if (ray_hit_cone_body(cone, ray, &body))
	{
		*rec = body;
		return (true);
	}
	else
		return (false);
}

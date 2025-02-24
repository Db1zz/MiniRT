#include "minirt.h"

// cn->pos is cap point; base is base of cone; apex is apex of cone
// r[0] is radius of cap point; r[1] is radius of base;

// bool	find_cone_solutions(const t_cone *cn, const t_ray *ray, double *t)
// {
// 	double		n[7];

// 	n[0] = 
// 	return (true);
// }

// bool	check_height(const t_cone *cn, const t_ray *ray, double *t)
// {
// 	t_vector	intersection_p;
// 	t_vector	base;
// 	t_vector	apex;
// 	double		height;

// 	base = vec3_add_vec3(cn->pos, vec3_mult(cn->axis, cn->height / 2));
// 	apex = vec3_add_vec3(cn->pos, vec3_div(vec3_mult(vec3_sub_vec3(base, cn->pos), cn->diameter / 2), cn->diameter / 2 - cn->diameter / 4));
// 	intersection_p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, t[0] < t[1] ? t[0] : t[1]));
// 	height = vec3_dot(vec3_sub_vec3(intersection_p, apex), cn->axis);
// 	if (height < 0 || height > cn->height)
// 		return (false);
// 	return (true);
// }

// t_vector	calc_cone_normal(const t_cone *cn, t_vector intersection_p)
// {
// 	t_vector	base;

// 	base = vec3_add_vec3(cn->pos, vec3_mult(cn->axis, cn->height / 2));
// 	return (vec3_normalize(vec3_sub_vec3(intersection_p, base)));
// }

// bool	ray_hit_cone_body(const t_cone *cone, const t_ray *ray, t_hit_record *rec)
// {
// 	double		t[2];

// 	if (!find_cone_solutions(cone, ray, t))
// 		return (false);
// 	if (!check_height(cone, ray, t))
// 		return (false);
// 	rec->ray_distance = t[0] < t[1] ? t[0] : t[1];
// 	rec->intersection_p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, rec->ray_distance));
// 	rec->normal = calc_cone_normal(cone, rec->intersection_p);
// 	rec->color = cone->color;
// 	rec->ray_direction = ray->direction;
// 	return (true);
// }

// static	t_object_list	*init_cap(const t_cone *cn)
// {
// 	t_plane			*cap_plane;
// 	t_object_list	*cap;

// 	cap_plane = malloc(sizeof(t_plane));
// 	cap_plane[0].pos = vec3_mult(cn->pos, 1);
// 	cap_plane[0].normal_vec = vec3_mult(cn->axis, -1);
// 	cap_plane[0].color = cn->color;
// 	cap = alloc_new_object(&cap_plane[0], E_PLANE, NULL);
// 	return (cap);
// }

// bool	ray_hit_cone_cap(const t_cone *cn, const t_ray *ray, t_hit_record *rec)
// {
// 	t_object_list	*cap;
// 	t_hit_record	cap_rec;

// 	init_hit_record(&cap_rec);
// 	cap = init_cap(cn);
// 	if (ray_hit_plane(cap, ray, &cap_rec))
// 	{
// 		if (vec3_distance(cap_rec.intersection_p, cn->pos) <= cn->diameter / 2)
// 		{
// 			*rec = cap_rec;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// bool	ray_hit_cone(const t_object_list *objects, const t_ray *ray, t_hit_record *rec)
// {
// 	const t_cone	*cone;
// 	t_hit_record	body_rec;
// 	t_hit_record	cap_rec;
// 	bool			hit[2];

// 	if (objects->type != E_CONE || objects->data == NULL)
// 		return (false);
// 	cone = (const t_cone *)objects->data;
// 	init_hit_record(&body_rec);
// 	init_hit_record(&cap_rec);
// 	hit[0] = ray_hit_cone_body(cone, ray, &body_rec);
// 	hit[1] = ray_hit_cone_cap(cone, ray, &cap_rec);
// 	if (hit[0] && hit[1])
// 	{
// 		if (body_rec.ray_distance < cap_rec.ray_distance)
// 			*rec = body_rec;
// 		else
// 			*rec = cap_rec;
// 	}
// 	else if (hit[0])
// 		*rec = body_rec;
// 	else if (hit[1])
// 		*rec = cap_rec;
// 	else
// 		return (false);
// 	return (true);
// }

#include "minirt.h"
#include "ray.h"

void	set_cylbody_hit(t_hit_record *rec, const t_ray *ray, double t[2], t_cylinder *cylinder)
{
	if (t[0] < t[1] && t[0] > 0)
		rec->ray_distance = t[0];
	else if (t[1] > 0)
		rec->ray_distance = t[1];
	rec->intersection_p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, rec->ray_distance));
	rec->normal = vec3_normalize(vec3_sub_vec3(rec->intersection_p, vec3_add_vec3(cylinder->pos, vec3_mult(cylinder->axis, vec3_dot(vec3_sub_vec3(rec->intersection_p, cylinder->pos), cylinder->axis)))));
	rec->color = cylinder->color;
	rec->obj_type = E_CYLINDER;
}

bool	ray_hit_body(t_cylinder *cylinder, const t_ray *ray, t_hit_record *rec)
{
	t_vector	delta_p;
	t_vector	tmp[2];
	double		a;
	double		b;
	double		c;
	double 		discriminant;
	double		t[2];
	double		y[2];

	delta_p = vec3_sub_vec3(ray->origin, cylinder->pos);
	tmp[0] = vec3_sub_vec3(ray->direction, vec3_mult(cylinder->axis, vec3_dot(ray->direction, cylinder->axis)));
	tmp[1] = vec3_sub_vec3(delta_p, vec3_mult(cylinder->axis, vec3_dot(delta_p, cylinder->axis)));
	a = vec3_dot(tmp[0], tmp[0]);
	b = vec3_dot(tmp[0], tmp[1]) * 2.0;
	c = vec3_dot(tmp[1], tmp[1]) - pow(cylinder->diameter / 2, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t[0] = (-b + sqrt(discriminant)) / (2 * a);
	t[1] = (-b - sqrt(discriminant)) / (2 * a);
	y[0] = vec3_dot(cylinder->axis, vec3_add_vec3(ray->origin, vec3_mult(ray->direction, t[0])));
    y[1] = vec3_dot(cylinder->axis, vec3_add_vec3(ray->origin, vec3_mult(ray->direction, t[1])));
    if ((y[0] < 0 || y[0] > cylinder->height) && (y[1] < 0 || y[1] > cylinder->height))
	{
    	return (false);
	}
	set_cylbody_hit(rec, ray, t, cylinder);
	return (true);
}

bool	ray_hit_caps(t_cylinder *cylinder, const t_ray *ray, t_hit_record *rec)
{
	double		t;
	t_vector	intersection_p;
	t_vector	normal;
	double		denom;
	double		hit_height;

	normal = vec3_negate(cylinder->axis);
	denom = vec3_dot(normal, ray->direction);
	if (fabs(denom) > 1e-6)
	{
		t = vec3_dot(vec3_sub_vec3(cylinder->pos, ray->origin), normal) / denom;
		if (t >= 0)
		{
			intersection_p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, t));
			hit_height = vec3_dot(cylinder->axis, vec3_sub_vec3(intersection_p, cylinder->pos));
			if (hit_height >= 0 && hit_height <= cylinder->height)
			{
				rec->ray_distance = t;
				rec->intersection_p = intersection_p;
				rec->normal = normal;
				rec->color = cylinder->color;
				rec->obj_type = E_CYLINDER;
				return (true);
			}
		}
	}
	normal = cylinder->axis;
	denom = vec3_dot(normal, ray->direction);
	if (fabs(denom) > 1e-6)
	{
		t = vec3_dot(vec3_sub_vec3(vec3_add_vec3(cylinder->pos, vec3_mult(cylinder->axis, cylinder->height)), ray->origin), normal) / denom;
		if (t >= 0)
		{
			intersection_p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, t));
			hit_height = vec3_dot(cylinder->axis, vec3_sub_vec3(intersection_p, cylinder->pos));
			if (hit_height >= 0 && hit_height <= cylinder->height)
			{
				rec->ray_distance = t;
				rec->intersection_p = intersection_p;
				rec->normal = normal;
				rec->color = cylinder->color;
				rec->obj_type = E_CYLINDER;
				return (true);
			}
		}
	}

	return (false);
}

bool	ray_hit_cylinder(const t_object_list *cylinder_object, const t_ray *ray, t_hit_record *rec)
{
	t_cylinder		*cylinder;
	t_hit_record	body;

	if (cylinder_object->type != E_CYLINDER || cylinder_object->data == NULL)
		return (false);
	cylinder = (t_cylinder *)cylinder_object->data;
	if (ray_hit_body(cylinder, ray, &body))
	{
		*rec = body;
		return (true);
	}
	else
		return (false);
}

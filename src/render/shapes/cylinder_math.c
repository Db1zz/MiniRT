#include "minirt.h"
#include "ray.h"
#include "vector.h"

t_vector    vec3_rotate(t_vector r1, t_vector r2, t_vector r3, t_vector p)
{
    t_vector    v;

    v.x = vec3_dot(r1, p);
    v.y = vec3_dot(r2, p);
    v.z = vec3_dot(r3, p);
    return (v);
}

t_vector    vec3_rotate_back(t_vector r1, t_vector r2, t_vector r3, t_vector p)
{
    t_vector    v;

    v.x = p.x * r1.x + p.y * r2.x + p.z * r3.x;
    v.y = p.y * r1.y + p.y * r2.y + p.z * r3.y;
    v.z = p.z * r1.z + p.y * r2.z + p.z * r3.z;
    return (v);
}

void    get_perpendicular_vector(t_vector v, t_vector *perp)
{
    if (v.x == 0 && v.y == 0)
    {
        perp->x = 1;
        perp->y = 0;
        perp->z = 0;
    }
    else
    {
        perp->x = -v.y;
        perp->y = v.x;
        perp->z = 0;
    }
}

void    set_cylbody_hit(t_hit_record *rec, const t_ray *ray, double t[2], t_cylinder *cylinder)
{
    t_vector    pa[2];
    t_vector    pt;

    if (t[0] < t[1] && t[0] > 0)
        rec->ray_distance = t[0];
    else if (t[1] >= 0)
        rec->ray_distance = t[1];
    rec->intersection_p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, rec->ray_distance));
    get_perpendicular_vector(cylinder->axis, &pa[0]);
    pa[1] = vec3_cross(cylinder->axis, pa[0]);
    pt = vec3_sub_vec3(rec->intersection_p, cylinder->pos);
    pt = vec3_normalize(vec3_rotate(pa[0], pa[1], cylinder->axis, pt));
    rec->normal = vec3_normalize(vec3_rotate_back(pa[0], pa[1], cylinder->axis, pt));
    rec->color = cylinder->color;
    rec->obj_type = E_CYLINDER;
	rec->ray_direction = vec3_normalize(ray->direction);
}
bool    ray_hit_body(t_cylinder *cylinder, const t_ray *ray, t_hit_record *rec)
{
    t_vector    delta_p;
    t_vector    tmp[2];
    double      a;
    double      b;
    double      c;
    double      discriminant;
    double      t[2];
    double      y[2];

	/*
		v == ray_dir
		p == ray_origin

		p:a == cylinder_pos
		v:a == cylinder_axis
		
		()
	*/

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
void    set_cap_hit(t_cylinder *cylinder, const t_ray *ray, t_hit_record *rec, double t)
{
    rec->ray_distance = t;
    rec->intersection_p = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, rec->ray_distance));
    rec->color = cylinder->color;
    rec->obj_type = E_CYLINDER;
}
bool    ray_hit_caps(t_cylinder *cylinder, const t_ray *ray, t_hit_record *rec)
{
    double      t[2];
    t_vector    q;
    t_vector    p2;
    double      tmp[3];
    double      dist;
    tmp[0] = vec3_dot(ray->direction, cylinder->axis);
    p2 = vec3_add_vec3(cylinder->pos, vec3_mult(cylinder->axis, cylinder->height));
    if (fabs(tmp[0]) < 1e-6)
        return (false);
    tmp[1] = vec3_dot(cylinder->axis, vec3_sub_vec3(cylinder->pos, ray->origin));
    tmp[2] = vec3_dot(cylinder->axis, vec3_sub_vec3(p2, ray->origin));
    t[0] = tmp[1] / tmp[0];
    t[1] = tmp[2] / tmp[0];
    if (t[0] > 0 && (t[0] < t[1] || t[1] <= 0))
        rec->ray_distance = t[0];
    else if (t[1] > 0 && (t[1] < t[0] || t[0] <= 0))
        rec->ray_distance = t[1];
    else
        return (false);
    q = vec3_add_vec3(ray->origin, vec3_mult(ray->direction, rec->ray_distance));
    if (rec->ray_distance == t[0])
        dist = vec3_length_squared(vec3_sub_vec3(q, cylinder->pos));
    else
        dist = vec3_length_squared(vec3_sub_vec3(q, p2));
    if (dist > pow(cylinder->diameter / 2, 2))
        return (false);
    set_cap_hit(cylinder, ray, rec, rec->ray_distance);
    if (rec->ray_distance == t[0])
        rec->normal = vec3_negate(cylinder->axis);
    else
        rec->normal = cylinder->axis;
    return (true);
}
bool    ray_hit_cylinder(const t_object_list *cylinder_object, const t_ray *ray, t_hit_record *rec)
{
    t_cylinder      *cylinder;
    t_hit_record    body;
    t_hit_record    caps;
    bool            hit[2];
    if (cylinder_object->type != E_CYLINDER || cylinder_object->data == NULL)
        return (false);
    cylinder = (t_cylinder *)cylinder_object->data;
	init_hit_record(&body);
	// init_hit_record(&caps);
    hit[0] = ray_hit_body(cylinder, ray, &body);
    // hit[1] = ray_hit_caps(cylinder, ray, &caps);
    // if (hit[0] && hit[1])
    // {
    //     if (body.ray_distance < caps.ray_distance)
    //         *rec = body;
    //     else
    //         *rec = caps;
    //     return (true);
    // }
    if (hit[0])
    {
		print_vec3(&body.normal);
        *rec = body;
        return (true);
    }
    // else if (hit[1])
    // {
    //     *rec = caps;
    //     return (true);
    // }
    else
        return (false);
}
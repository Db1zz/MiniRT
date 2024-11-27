#include "camera.h"
#include "vector.h"
#include "scene.h"
#include "minirt_math.h"
#include "minirt.h"

static t_ray	create_ray(t_vector origin, t_vector direction)
{
	return ((t_ray){origin, direction, (t_color){0, 0, 0}});
}

static t_color	ray_color(const t_ray *r, const t_hit_record *hit_rec)
{
	t_vector	u_vec;
	t_vector	color_vec;

	if (hit_rec != NULL)
	{
		u_vec = vec3_add_vec3(r->origin, vec3_mult(r->direction, hit_rec->t));
		u_vec = vec3_sub_vec3(u_vec, (t_vector){0, 0, -1});
		u_vec = vec3_normalize(u_vec);
		color_vec = vec3_mult(vec3_mult(vec3_add(u_vec, 1), 0.5), 255);
		return ((t_color){color_vec.x, color_vec.y, color_vec.z});
	}
	u_vec = r->direction;
    double a = 0.5 * (u_vec.y + 1.0);
	t_vector res = vec3_mult(vec3_add_vec3(
			vec3_mult((t_vector){1.0, 1.0, 1.0}, 1.0 - a), 
			vec3_mult((t_vector){0.5, 0.7, 1}, a)), 255);
	return ((t_color){res.x, res.y, res.z});
}

static t_vector	camera_get_pixel_center(const t_camera *camera, int x, int y)
{	
	const t_viewport	*viewport = &camera->viewport;
	t_vector			pixel_center;

	pixel_center = vec3_add_vec3(viewport->upper_left,
					vec3_add_vec3(
						vec3_mult(viewport->pdelta_x, y),
						vec3_mult(viewport->pdelta_y, x)));
	return (pixel_center);
}

static t_color	camera_hit_ray(const t_scene *scene, const t_ray *ray)
{
	t_hit_record	rec;

	if (ray_hit_sphere(scene->spheres, ray, (double[2]){0, M_INFINITY}, &rec))
		return (ray_color(ray, &rec));
	return (ray_color(ray, NULL));
}

t_color	camera_send_ray(const t_camera *camera, const t_scene *scene,
		int x, int y)
{
	t_vector	ray_direction;
	t_vector	pixel_center;
	t_ray		ray;
	t_color		ray_color;

	pixel_center = camera_get_pixel_center(camera, x, y);
	ray_direction = vec3_sub_vec3(pixel_center, camera->view_point);
	ray = create_ray(camera->view_point, ray_direction);
	ray_color = camera_hit_ray(scene, &ray);
	return (ray_color);
}

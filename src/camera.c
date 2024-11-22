#include "camera.h"
#include "vector.h"
#include "scene.h"

static t_ray	create_ray(t_vector origin, t_vector direction)
{
	return ((t_ray){origin, direction, (t_color){0, 0, 0}});
}

static t_color ray_color(const t_ray *r, double discriminant)
{
	t_vector	u_vec;
	t_vector	color_vec;

	if (discriminant > 0)
	{
		u_vec = vec3_add_vec3(r->origin, vec3_mult(r->direction, discriminant));
		u_vec = vec3_sub_vec3(u_vec, (t_vector){0, 0, -1});
		u_vec = vec3_normalize(u_vec);
		color_vec = vec3_mult(vec3_add(u_vec, 1), 0.5);
		return ((t_color){color_vec.x, color_vec.y, color_vec.z});
	}
	return ((t_color){255, 255, 255});
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
	double	t = ray_hit_sphere(scene->spheres, ray);
	return (ray_color(ray, t));
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

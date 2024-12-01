#include "camera.h"
#include "minirt_math.h"

static t_vector	camera_get_pixel_center(const t_scene *scene, int x, int y)
{	
	const t_viewport	*viewport = &scene->camera->viewport;
	t_vector			pixel_center;
	t_vector			offset;

	offset = (t_vector){0, 0, 0};
	if (scene->antialiasing)
		offset = get_random_vector_offset():
	pixel_center = vec3_add_vec3(viewport->first_pixel,
					vec3_add_vec3(
						vec3_mult(viewport->pdelta_x, y + offset.y),
						vec3_mult(viewport->pdelta_y, x + offset.x)));
	return (pixel_center);
}

t_color	camera_send_ray(const t_camera *camera, const t_scene *scene,
		int x, int y)
{
	t_vector	ray_direction;
	t_vector	pixel_center;
	t_ray		ray;
	t_color		ray_color;
	t_interval	interval;

	pixel_center = camera_get_pixel_center(scene, x, y);
	ray_direction = vec3_sub_vec3(pixel_center, camera->view_point);
	ray = create_ray(camera->view_point, ray_direction);
	interval = create_interval(0, FT_INFINITY);
	return (ray_color);
}

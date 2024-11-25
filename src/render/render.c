#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"

void	hit_record_set_face_normal(const t_ray *ray,
			const t_vector *outward_normal, t_hit_record *rec)
{
	rec->front_face = vec3_dot(ray->direction, *outward_normal) < 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = vec3_mult(*outward_normal, -1);
}

void	render(t_scene *scene)
{
	int		x;
	int		y;
	t_color	ray_color;

	x = 0;
	while (x < WIN_HEIGHT)
	{
		y = 0;
		while (y < WIN_WIDTH)
		{
			ray_color = camera_send_ray(scene->camera, scene, x, y);
			draw_pixel(scene, y, x, ray_color);
			y++;
		}
		x++;
	}
}

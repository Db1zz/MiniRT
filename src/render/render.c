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
	const double	color_scale = 1.0 / ANTIALIASING_SAMPLES;
	int				x;
	int				y;
	int				pixel_samples;
	t_color			ray_color;

	x = 0;
	ray_color = (t_color){0,0,0};
	while (x < WIN_HEIGHT)
	{
		y = 0;
		while (y < WIN_WIDTH)
		{
			/*
				double color_k = 1.0;
				const int color_samples = 2;
				color_k = color_k / color_samples;
				t_color ray_color(0,0,0);
				ray_color += camera_send_ray():
				return ((t_color)vec3_mult(ray_color, (t_vector)t_color));
			*/
			pixel_samples = 0;
			while (pixel_samples++ < ANTIALIASING_SAMPLES)
				ray_color = clr_add_clr(ray_color, camera_send_ray(scene->camera, scene, x, y));
			ray_color = color_mult(ray_color, color_scale);
			draw_pixel(scene, y, x, ray_color);
			y++;
		}
		x++;
	}
}

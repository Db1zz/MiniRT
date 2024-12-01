#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"
#include "minirt_math.h"

t_color	apply_antialiasing(t_color ray_color, t_scene *scene, int x, int y)
{
	const double		color_scale = (double)(1.0 / ANTIALIASING_SAMPLES);
	const t_interval	interval = create_interval(0.0, 255.0);
	int					pixel_samples;

	pixel_samples = 0;
	while (pixel_samples < ANTIALIASING_SAMPLES)
	{
		ray_color = clr_add_clr(ray_color,
				camera_send_ray(scene->camera, scene, x, y));
		pixel_samples++;
	}
	ray_color = clr_mult(ray_color, color_scale);
	ray_color.r = interval_bound(ray_color.r, &interval);
	ray_color.g = interval_bound(ray_color.g, &interval);
	ray_color.b = interval_bound(ray_color.b, &interval);
	return (ray_color);
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
			ray_color = apply_antialiasing(ray_color, scene, x, y);
			draw_pixel(scene, y, x, ray_color);
			y++;
		}
		x++;
	}
}

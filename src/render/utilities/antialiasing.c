#include "minirt.h"
#include "interval.h"
#include "color.h"
#include "camera.h"

t_color	apply_antialiasing(t_color ray_color, t_scene *scene, int x, int y)
{
	const double		color_scale = (double)(1.0 / ANTIALIASING_SAMPLES);
	const t_interval	interval = create_interval(0.0, 255.0);
	int					pixel_samples;

	pixel_samples = 0;
	while (pixel_samples < ANTIALIASING_SAMPLES)
	{
		ray_color = clr_add_clr(ray_color,
				camera_get_pixel_color(scene->camera, scene, x, y));
		pixel_samples++;
	}
	ray_color = clr_mult(ray_color, color_scale);
	ray_color.r = interval_bound(ray_color.r, &interval);
	ray_color.g = interval_bound(ray_color.g, &interval);
	ray_color.b = interval_bound(ray_color.b, &interval);
	return (ray_color);
}
#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"

void	ray_tracing(t_scene *scene)
{
	int			x;
	int			y;
	t_color		ray_color;

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

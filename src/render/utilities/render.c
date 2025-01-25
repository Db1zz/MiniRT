#include "camera.h"
#include "minirt.h"
#include "color.h"
#include "scene.h"

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
			ray_color = camera_get_pixel_color(scene->camera, scene, x, y);
			ray_color = apply_antialiasing(ray_color, scene, x, y);
			draw_pixel(scene, y, x, ray_color);
			y++;
		}
		x++;
	}
}

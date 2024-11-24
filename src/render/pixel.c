#include "minirt.h"
#include "vector.h"
#include "color.h"
#include "scene.h"
#include "mlx.h"

void	draw_pixel(t_scene *scene, int x, int y, t_color color)
{
	mlx_pixel_put(scene->mlx, scene->win, x, y, rgb_to_int(color));
}

#include "minirt.h"
#include "vector.h"
#include "color.h"
#include "scene.h"
#include "mlx.h"

/*
    We cannot use bit shifting because of big-endian and little-endian systems.
*/
int rgb_to_int(t_color *color)
{
    return (65536 * color->r + 256 * color->g + color->b);
}

void	draw_pixel(t_scene *scene, int x, int y, t_color *color)
{
	mlx_pixel_put(scene->mlx, scene->win, x, y, rgb_to_int(color));
}

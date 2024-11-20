#include "minirt.h"
#include "vector.h"
#include "color.h"
#include "scene.h"
#include "mlx.h"

int rgb_to_int(t_color *color)
{
    int hex_color = 0;

    hex_color |= (int)(color->b * 255);
    hex_color |= (int)(color->g * 255) << 8;
    hex_color |= (int)(color->r * 255) << 16;
    return (hex_color);
}

void	draw_pixel(t_scene *scene, int x, int y, t_color *color)
{
	mlx_pixel_put(scene->mlx, scene->win, x, y, rgb_to_int(color));
}

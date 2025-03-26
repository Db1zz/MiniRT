#include "xpm_render.h"

t_xpm_image xpm_render_new_img(struct t_xvar *mlx, int width, int height) {
	t_xpm_image	image;

	image.img = mlx_new_image(mlx, width, height);
	image.data = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.size_line, &image.endian);
	image.width = width;
	image.height = height;

	return (image);
}

bool xpm_render_put_pixel(t_xpm_image *img, int x, int y, const t_color *color) {
	if (x > img->height || y > img->width) {
		return (false);
	}

	image.data[x][y] = 
	return (true);
}
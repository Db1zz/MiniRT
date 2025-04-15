#include "xpm_render.h"
#include "mlx.h"
#include <assert.h>
#include <stdlib.h>

/*
	Documentation:
	https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html#mlx_get_data_addr

*/
t_xpm_image xpm_render_new_img(void *mlx, int width, int height)
{
	t_xpm_image img;

	img.img = mlx_new_image(mlx, width, height);
	assert(img.img != NULL);
	img.data = (unsigned char *)mlx_get_data_addr(
		img.img,
		&img.bits_per_pixel,
		&img.size_line,
		&img.endian);
	assert(img.data != NULL);
	img.width = width;
	img.height = height;
	img.mlx = mlx;
	img.bytes_per_pixel = img.bits_per_pixel / 8;
	return (img);
}

void xpm_render_put_pixel(
	t_xpm_image *img,
	unsigned int x,
	unsigned int y,
	const t_color *color)
{
	unsigned int int_color;
	unsigned char *ptr;

	int_color = mlx_get_color_value(img->mlx, rgb_to_int(*color));
	int pos = x * img->size_line + y * img->bytes_per_pixel;
	ptr = img->data + pos;
	ptr[0] = ((unsigned char *)&int_color)[0];
	ptr[1] = ((unsigned char *)&int_color)[1];
	ptr[2] = ((unsigned char *)&int_color)[2];
	ptr[3] = ((unsigned char *)&int_color)[3];
}
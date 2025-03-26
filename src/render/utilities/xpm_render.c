#include "xpm_render.h"
#include <mlx.h>
#include <assert.h>

/*
	Documentation:
	https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html#mlx_get_data_addr

*/
t_xpm_image	xpm_render_new_img(void *mlx, int width, int height) {
	t_xpm_image	img;

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
}

void	xpm_render_put_pixel(
	t_xpm_image *img,
	unsigned int x,
	unsigned int y,
	const t_color *color)
{
	unsigned int int_color;
	unsigned char *ptr;

	assert((x < img->height && y < img->width));

	/*
		0 0 0 0 0 0 0 0 - 0
		0 0 0 0 0 0 0 0 - 1
		0 0 0 0 0 0 0 0 - 2
		0 0 0 0 0 0 0 0 - 3
	*/

	int_color = mlx_get_color_value(img->mlx, rgb_to_int(*color));
	int pos = y * img->size_line + x * img->bytes_per_pixel;
	printf("pos: %d\n", pos);
	ptr = img->data + pos;
	*ptr = 10; // ((unsigned char *)&int_color)[0];
}
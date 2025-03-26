#ifndef XPM_RENDER_H
# define XPM_RENDER_H

#include <mlx.h>
#include <scene.h>

typedef struct t_xpm_image {
	unsigned int width;
	unsigned int height;
	int bits_per_pixel;
	int size_line;
	int endian;
	unsigned char *data;
	struct t_img *img;
} t_xpm_image;


#endif  // XPM_RENDER_H
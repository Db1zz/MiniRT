#ifndef XPM_RENDER_H
# define XPM_RENDER_H

#include <scene.h>
#include "mlx.h"

/*

	typedef struct s_xpm_canvas
	{
		t_xvar			*mlx;
		void			*img;
		unsigned char	*data;
		int				bpp;
		int				opp;
		int				xpm_line_len;
		int				endian;
	}	t_xpm_canvas;

*/
typedef struct s_xpm_image
{
	struct t_xvar	*mlx;
	void			*img;
	unsigned char	*data;
	unsigned int	width;
	unsigned int	height;
	int 			bits_per_pixel;
	int				bytes_per_pixel;
	int 			size_line;
	int 			endian;
}	t_xpm_image;

void		xpm_render_put_pixel(
	t_xpm_image *img,
	unsigned int x,
	unsigned int y,
	const t_color *color);

/*
	Hueta)
*/
t_xpm_image	xpm_render_new_img(
	void *mlx,
	int width,
	int height);

#endif  // XPM_RENDER_H
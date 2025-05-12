/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:23:51 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 14:23:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xpm_render.h"

#include "mlx.h" /* mlx shit */

#include <stdlib.h> /* free */

t_xpm_image	*xpm_render_new_img(void *mlx, int width, int height)
{
	t_xpm_image	*img;

	img = calloc(1, sizeof(t_xpm_image));
	img->img = mlx_new_image(mlx, width, height);
	img->data = (unsigned char *)mlx_get_data_addr(
			img->img,
			&img->bits_per_pixel,
			&img->size_line,
			&img->endian);
	img->width = width;
	img->height = height;
	img->mlx = mlx;
	img->bytes_per_pixel = img->bits_per_pixel / 8;
	return (img);
}

void	xpm_render_put_pixel(
	t_xpm_image *img,
	unsigned int x,
	unsigned int y,
	const t_color *color)
{
	unsigned int	int_color;
	int				pos;

	int_color = mlx_get_color_value(img->mlx, rgb_to_int(color));
	pos = x * img->size_line + y * img->bytes_per_pixel;
	*(unsigned int *)(img->data + pos) = int_color;
}

void	xpm_render_destroy_img(void *mlx, t_xpm_image *img)
{
	mlx_destroy_image(mlx, img->img);
	free(img);
}

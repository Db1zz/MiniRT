/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:35:45 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:35:45 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_RENDER_H
# define XPM_RENDER_H

# include "color.h" /* t_color */

typedef struct s_xpm_image
{
	void			*img;
	void			*mlx;
	unsigned char	*data;
	unsigned int	width;
	unsigned int	height;
	int				bits_per_pixel;
	int				bytes_per_pixel;
	int				size_line;
	int				endian;
}	t_xpm_image;

t_xpm_image	*xpm_render_new_img(
				void *mlx,
				int width,
				int height);

void		xpm_render_put_pixel(
				t_xpm_image *img,
				unsigned int x,
				unsigned int y,
				const t_color *color);

void		xpm_render_destroy_img(
				void *mlx,
				t_xpm_image *img);

#endif  // XPM_RENDER_H
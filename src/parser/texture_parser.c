/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:28 by gonische          #+#    #+#             */
/*   Updated: 2025/05/07 18:41:43 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h" 
#include "mlx.h"
#include "scene.h"
#include "minirt.h"
#include "libft.h"

t_texture	*parse_texture(t_scene *scene, char *filename)
{
	t_texture	*texture;
	int			x;
	int			y;
	int			z;

	if (!filename)
		return (NULL);
	texture = malloc(sizeof(t_texture));
	texture->img = mlx_xpm_file_to_image(
			scene->mlx, filename, &texture->width, &texture->height);
	texture->mlx = scene->mlx;
	if (!texture->img)
	{
		set_error(&scene->error, ERR_OPEN_TEXTURE_FAILURE, __func__);
		free(texture);
		return (NULL);
	}
	texture->pixels = (int *)mlx_get_data_addr(texture->img, &x, &y, &z);
	return (texture);
}

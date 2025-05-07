/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:28 by gonische          #+#    #+#             */
/*   Updated: 2025/05/07 16:45:17 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h" 
#include "mlx.h"
#include "scene.h"
#include "minirt.h"

t_texture	*parse_texture(t_scene *scene, char *filename)
{
	t_texture	*texture;
	void		*img;
	int			x;
	int			y;
	int			z;

	if (!filename)
		return (NULL);
	texture = malloc(sizeof(t_texture));
	img = mlx_xpm_file_to_image(
			scene->mlx, "./textures/sand.xpm", &texture->width, &texture->height);
	texture->pixels = (int *)mlx_get_data_addr(img, &x, &y, &z);
	return (texture);
}

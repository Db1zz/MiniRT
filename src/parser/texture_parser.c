/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:28 by gonische          #+#    #+#             */
/*   Updated: 2025/05/06 13:22:57 by gwagner          ###   ########.fr       */
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
	char		*tmp;
	int			x;
	int			y;
	int			z;

	if (!filename)
		return (NULL);
	texture = malloc(sizeof(t_texture));
	ft_printf("%s\n", filename);
	img = mlx_xpm_file_to_image(
			scene->mlx, filename, &texture->width, &texture->height);
	if (!img)
		ft_printf("SOME BS HAPPENED!\n");
	tmp = (int *)mlx_get_data_addr(img, &x, &y, &z);
	texture->pixels = (int *)tmp;
	mlx_destroy_image(scene->mlx, img);
	return (texture);
}

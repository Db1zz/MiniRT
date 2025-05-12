/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:11:56 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 14:11:56 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

#include "mlx.h"

#include <stdlib.h> /* free() */

static void	scene_destroy_object_array(t_object **objects)
{
	int	i;

	i = 0;
	while (objects[i])
		object_destroy(&objects[i++]);
	free(objects);
}

#ifdef __APPLE__
/*
	mlx is a cross-platform library they said))))))
*/
static void	mlx_destroy_display(void *mlx)
{
	(void)mlx;
}

#endif // __APPLE__

void	scene_destroy(t_scene *scene)
{
	scene_destroy_object_array(scene->ambient_light);
	scene_destroy_object_array(scene->lights);
	scene_destroy_object_array(scene->objects);
	free_bvh_tree(scene->tree);
	if (scene->img)
		xpm_render_destroy_img(scene->mlx, scene->img);
	if (scene->camera)
		free(scene->camera);
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->mlx)
		(mlx_destroy_display(scene->mlx), free(scene->mlx));
}

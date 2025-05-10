/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:46:03 by gonische          #+#    #+#             */
/*   Updated: 2025/05/07 18:40:13 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

#include "object.h" /* t_object */
#include "libft.h" /* ft_calloc */
#include "viewport.h" /* update_viewport + viewport dimensions */
#include "mlx.h" /* mlx stuff */
#include "ray.h" /* create_ray() | ray_trace_bvh_color() */

#include <stdlib.h> /* free() */

t_error	scene_init(t_scene *scene)
{
	scene = ft_memset(scene, 0, sizeof(t_scene));
	scene->objects = ft_calloc(SCENE_OBJECTS_LIMIT + 1, sizeof(t_object *));
	scene->lights = ft_calloc(SCENE_LIGHTS_LIMIT + 1, sizeof(t_object *));
	scene->ambient_light
		= ft_calloc(SCENE_AMBIENT_LIGHTNING_LIMIT + 1, sizeof(t_object *));
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(
			scene->mlx,
			VIEWPORT_WIDTH,
			VIEWPORT_HEIGHT,
			"The rats have taken over");
	scene->img = xpm_render_new_img(
			scene->mlx,
			VIEWPORT_WIDTH,
			VIEWPORT_HEIGHT);
	return (scene->error);
}

void	scene_update_tree(t_scene *scene)
{
	free_bvh_tree(scene->tree);
	scene->tree = create_tree(scene->objects, 0, scene->objects_size - 1, 0);
}

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
void	mlx_destroy_display(void *mlx)
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

t_color	scene_calculate_pixel_color(
	const t_camera *camera,
	const t_scene *scene,
	int x, int y)
{
	t_vector	ray_direction;
	t_ray		ray;

	ray_direction = camera_calculate_ray_direction(camera, y, x);
	ray = create_ray(
			camera->view_point, ray_direction, create_color(0, 0, 0), 0);
	return (ray_trace_bvh_color(&ray, scene->tree, scene));
}

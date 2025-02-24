/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:30 by gonische          #+#    #+#             */
/*   Updated: 2025/02/11 18:27:31 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "scene.h"
#include "vector.h"
#include "ray.h"
#include "minirt.h"
#include "minirt_math.h"

static t_vector	camera_get_pixel_center(const t_scene *scene, int x, int y)
{
	const t_viewport	*viewport = &scene->camera->viewport;
	t_vector			pixel_center;
	t_vector			offset;

	offset = create_vector(0, 0, 0);
	if (scene->antialiasing)
		offset = get_random_vector_offset();
	pixel_center = vec3_add_vec3(viewport->first_pixel,
			vec3_add_vec3(
				vec3_mult(viewport->pdelta_x, y + offset.y),
				vec3_mult(viewport->pdelta_y, x + offset.x)));
	return (pixel_center);
}

static t_vector	camera_calculate_ray_direction(
	const t_vector *pixel_center,
	const t_camera *camera)
{
	t_vector	ray_origin;
	t_vector	ray_direction;

	ray_origin = vec3_add_vec3(camera->view_point, camera->orientation_vec);
	ray_direction = vec3_normalize(vec3_sub_vec3(*pixel_center, ray_origin));
	return (ray_direction);
}

t_color	camera_get_pixel_color(
	const t_camera	*camera,
	const t_scene	*scene,
	int x, int y)
{
	t_vector	ray_direction;
	t_vector	pixel_center;
	t_ray		ray;

	pixel_center = camera_get_pixel_center(scene, x, y);
	ray_direction = camera_calculate_ray_direction(&pixel_center, camera);
	ray = create_ray(camera->view_point, ray_direction, create_color(0, 0, 0));
	return (ray_send(&ray, scene));
}

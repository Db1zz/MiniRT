/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:30 by gonische          #+#    #+#             */
/*   Updated: 2025/04/12 12:56:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "scene.h"
#include "vector.h"
#include "ray.h"
#include "minirt.h"
#include "minirt_math.h"
#include "aabb.h"

// static t_vector	camera_get_pixel_center(const t_scene *scene, int x, int y)
// {
// 	const t_viewport	*viewport = &scene->camera->viewport;
// 	t_vector			pixel_center;
// 	t_vector			offset;

// 	offset = create_vector(0, 0, 0);
// 	// if (scene->antialiasing)
// 	// 	offset = get_random_vector_offset();
// 	pixel_center = vec3_add_vec3(viewport->first_pixel,
// 			vec3_add_vec3(
// 				vec3_mult(viewport->pdelta_x, y + offset.y),
// 				vec3_mult(viewport->pdelta_y, x + offset.x)));
// 	return (pixel_center);
// }

// x[0] = -camera->orientation_vec
// x[1] = camera_right
// x[2] = camera_up
// x[3] = horizontal_vec
// x[4] = vertical_vec
// x[5] = lower_left_corner
// x[6] = offset
// x[7] = viewport_pos

static t_vector camera_calculate_ray_direction(
	const t_camera *camera,
	int x_pos, int y_pos)
{
	t_vector x[8];
	double fov;
	double aspect_ratio;

	aspect_ratio = (double)VIEWPORT_WIDTH / VIEWPORT_HEIGHT;
	fov = tan((FT_PI * 0.5 * camera->fov) / 180);
	x[0] = vec3_negate(camera->orientation_vec);
	if (camera->orientation_vec.y > 0 && camera->orientation_vec.x == 0 && camera->orientation_vec.z == 0)
		x[1] = vec3_negate(vec3_normalize(vec3_cross(camera->orientation_vec, create_vector(0, 0, 1))));
	else
		x[1] = vec3_negate(vec3_normalize(vec3_cross(camera->orientation_vec, create_vector(0, 1, 0))));
	// x[2] = vec3_cross(x[1], camera->orientation_vec);
	x[2] = vec3_cross(x[0], x[1]);
	x[3] = vec3_mult(x[1], 2 * aspect_ratio * fov);
	x[4] = vec3_mult(x[2], 2 * fov);
	x[5] = vec3_sub_vec3(
		vec3_sub_vec3(
			vec3_sub_vec3(camera->view_point,
						  vec3_mult(x[3], 0.5)),
			vec3_mult(x[4], 0.5)),
		x[0]);
	x[6] = vec3_add_vec3(vec3_mult(x[3], ((double)x_pos + 0.5) / VIEWPORT_WIDTH),
						 vec3_mult(x[4], ((double)y_pos + 0.5) / VIEWPORT_HEIGHT));
	x[7] = vec3_add_vec3(x[5], x[6]);
	return (vec3_normalize(vec3_sub_vec3(x[7], camera->view_point)));
}

t_color camera_get_pixel_color(
	const t_camera *camera,
	const t_scene *scene,
	const t_bvh_node *tree,
	int x, int y)
{
	t_vector ray_direction;
	// t_vector	pixel_center;
	t_ray ray;

	// pixel_center = camera_get_pixel_center(scene, x, y);
	ray_direction = camera_calculate_ray_direction(camera, y, x);
	ray = create_ray(camera->view_point, ray_direction, create_color(0, 0, 0));
	return (ray_hit_tree(&ray, tree, scene));
}

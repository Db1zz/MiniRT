/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:47:26 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:47:26 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h" /* t_vector */
# include "viewport.h" /* t_viewport */
# include "color.h" /* t_color */

# ifdef __APPLE__
#  include "key_macos.h"
# elif __linux__
#  include "key_linux.h"
# endif

# define CAMERA_FOV_MIN 0
# define CAMERA_FOV_MAX 180

typedef struct s_camera
{
	t_viewport	viewport;
	t_vector	view_point;
	t_vector	orientation_vec;
	int			fov;
}	t_camera;

t_vector	camera_calculate_ray_direction(
				const t_camera *camera,
				int x_pos, int y_pos);
void		camera_update_viewport(t_camera *camera);
int			camera_move_view_point(int key, t_camera *camera);
int			camera_change_orientation_vector(int key, t_camera *camera);

#endif // CAMERA_H

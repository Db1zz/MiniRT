/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:40:41 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 15:49:11 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
#define CAMERA_H

#include "pos.h"
#include "scene.h"

typedef struct s_camera
{
	t_pos	view_point;
	t_pos	orientation_vec;
	int		fov	; // 0 - 180
}	t_camera;

int	create_camera(t_scene *scene, const t_pos *view_point,
			const t_pos *orientation_vec, int fov);

#endif	// CAMERA_H

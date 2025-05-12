/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:36:49 by gwagner           #+#    #+#             */
/*   Updated: 2025/05/12 15:37:02 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "scene.h"
#include "vector.h"
#include "minirt_math.h"
#include <math.h>

void	camera_update_viewport(t_camera *camera)
{
	update_viewport(&camera->viewport, camera->fov, camera->view_point);
}

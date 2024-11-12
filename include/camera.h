#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "scene.h"

#define FOV_MIN 0
#define FOV_MAX 180

typedef struct s_camera
{
	t_vector	view_point;
	t_vector	orientation_vec;
	int			fov	; // 0 - 180
}	t_camera;

int	create_camera(t_scene *scene, const t_vector *view_point,
			const t_vector *orientation_vec, int fov);

#endif	// CAMERA_H

#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "viewport.h"
#include "object.h"
#include "ray.h"
#include "bvh.h"
#include <math.h>

#define CAMERA_FOV_MIN 0
#define CAMERA_FOV_MAX 180

typedef struct s_camera
{
	t_vector view_point;
	t_vector orientation_vec;
	int fov;
	t_viewport viewport;
} t_camera;

t_color camera_get_pixel_color(
	const t_camera *camera,
	const t_scene *scene,
	int x, int y);

#endif // CAMERA_H

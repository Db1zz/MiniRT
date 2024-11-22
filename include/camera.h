#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "viewport.h"
# include "shapes.h"

# define FOV_MIN 0
# define FOV_MAX 180

typedef struct s_camera
{
	t_vector	view_point;
	t_vector	orientation_vec;
	int			fov; // 0	 - 180
	t_viewport	viewport;
}	t_camera;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_color		color;
}	t_ray;

t_color	camera_send_ray(const t_camera *camera, const t_scene *scene,
		int x, int y);
double	ray_hit_sphere(const t_sphere *spheres, const t_ray *ray);

#endif	// CAMERA_H
		
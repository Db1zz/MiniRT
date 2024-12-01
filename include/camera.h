#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "viewport.h"
# include "object.h"
# include "ray.h"
# include <math.h> 

# define FOV_MIN 0
# define FOV_MAX 180

typedef struct s_camera
{
	t_vector	view_point;
	t_vector	orientation_vec;
	int			fov; // 0 - 180
	t_viewport	viewport;
}	t_camera;

/*
	Ray hit record related functions and typedefs
*/
t_color	camera_send_ray(const t_camera *camera, const t_scene *scene,
			int x, int y);
bool	ray_hit_sphere(const t_sphere *sphere, const t_ray *ray,
			double ray_t_min_max[2], t_hit_record *rec);
/*
    Sets the hit record normal vector.
    NOTE: the parameter `outward_normal` is assumed to have unit length.
*/
void	hit_record_set_face_normal(const t_ray *ray,
			const t_vector *outward_normal, t_hit_record *rec);

#endif	// CAMERA_H
		
#include "viewport.h"
#include "scene.h"
#include "minirt.h"

t_error	update_viewport(t_camera *cam)
{
	t_viewport	*vp;

	if (cam == NULL)
		return (1); // Set error "Viewport cannot be initialized without camera"
	vp = &cam->viewport;
	vp->height = 2.0;
	vp->width = vp->height * ((double)WIN_WIDTH / WIN_HEIGHT);
	vp->horizontal_vec.x = vp->width;
	vp->horizontal_vec.y = 0;
	vp->horizontal_vec.z = 0;
	vp->verical_vec.x = 0;
	vp->verical_vec.y = -vp->height;
	vp->verical_vec.z = 0;
	// vp->upper_left.x = cam->view_point.x - cam->orientation_vec.x - vp->horizontal_vec.x / 2 - vp->verical_vec.x / 2;
	/*
		auto viewport_upper_left = camera_center
                            - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
	*/
	vp->upper_left = vec3_sub_vec3(vec3_div(vp->horizontal_vec, 2.0), vec3_div(vp->horizontal_vec, 2.0));
	vp->upper_left = vec3_sub_vec3((t_vector){0.0, 0.0, cam->orientation_vec.z}, vp->upper_left);
	vp->upper_left = vec3_sub_vec3(cam->view_point, vp->upper_left);
	vp->pdelta_x = vec3_div(vp->horizontal_vec, WIN_WIDTH);
	vp->pdelta_y = vec3_div(vp->verical_vec, WIN_HEIGHT);
	vp->first_pixel = vec3_add_vec3(vp->upper_left,
		vec3_div(vec3_add_vec3(vp->pdelta_x, vp->pdelta_y), 2.0));
}

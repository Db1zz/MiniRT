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
	/* 
		auto viewport_upper_left = camera_center
                            - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
	*/
}
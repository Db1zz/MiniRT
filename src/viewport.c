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
	vp->horizontal_vec = (t_vector){vp->width, 0, 0};
	vp->verical_vec = (t_vector){0, -vp->height, 0};
	vp->upper_left = aboba(aboba(aboba(cam->view_point, (t_vector){0, 0, 1}),
		vec3_div(vp->horizontal_vec, 2.0)), vec3_div(vp->verical_vec, 2.0));
	vp->pdelta_x = vec3_div(vp->horizontal_vec, WIN_WIDTH);
	vp->pdelta_y = vec3_div(vp->verical_vec, WIN_HEIGHT);
	vp->first_pixel = vec3_add_vec3(vp->upper_left,
		vec3_mult(vec3_add_vec3(vp->pdelta_x, vp->pdelta_y), 0.5));
	return (0);
}

#include "viewport.h"
#include "minirt_math.h"
#include "scene.h"
#include "minirt.h"

double	fov_to_height(double fov)
{
	return (tan((FT_PI * 0.5 * fov) / 180));
}

void	update_viewport(t_camera *cam)
{
	t_viewport	*vp;

	vp = &cam->viewport;
	vp->height = fov_to_height(cam->fov);
	vp->width = ((double)WIN_WIDTH / WIN_HEIGHT) * vp->height;
	vp->horizontal_vec = create_vector(vp->width, 0, 0);
	vp->verical_vec = create_vector(0, -vp->height, 0);
	vp->upper_left = vec3_sub_vec3(vec3_sub_vec3(vec3_sub_vec3(cam->view_point, create_vector(0, 0, 1)),
		vec3_div(vp->horizontal_vec, 2.0)), vec3_div(vp->verical_vec, 2.0));
	vp->pdelta_x = vec3_div(vp->horizontal_vec, WIN_WIDTH);
	vp->pdelta_y = vec3_div(vp->verical_vec, WIN_HEIGHT);
	vp->first_pixel = vec3_add_vec3(vp->upper_left,
		vec3_mult(vec3_add_vec3(vp->pdelta_x, vp->pdelta_y), 0.5));
}

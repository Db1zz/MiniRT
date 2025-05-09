#include "camera.h"

#include "scene.h" /* t_scene */
#include "vector.h" /* t_vector | functions */
#include "minirt_math.h" /* FT_PI */

#include <math.h> /* tan() | cos() | sin() */

static t_vector camera_calculate_ray_direction(
	const t_camera *camera,
	int x_pos, int y_pos)
{
	t_vector x[8];
	double fov;
	double aspect_ratio;

	aspect_ratio = (double)VIEWPORT_WIDTH / VIEWPORT_HEIGHT;
	fov = tan((FT_PI * 0.5 * camera->fov) / 180);
	x[0] = vec3_negate(camera->orientation_vec);
	if (camera->orientation_vec.y > 0 && camera->orientation_vec.x == 0 && camera->orientation_vec.z == 0)
		x[1] = vec3_negate(vec3_normalize(vec3_cross(camera->orientation_vec, (t_vector){0, 0, 1})));
	else
		x[1] = vec3_negate(vec3_normalize(vec3_cross(camera->orientation_vec, (t_vector){0, 1, 0})));
	x[2] = vec3_cross(x[0], x[1]);
	x[3] = vec3_mult(x[1], 2 * aspect_ratio * fov);
	x[4] = vec3_mult(x[2], 2 * fov);
	x[5] = vec3_sub_vec3(
		vec3_sub_vec3(
			vec3_sub_vec3(camera->view_point,
						  vec3_mult(x[3], 0.5)),
			vec3_mult(x[4], 0.5)),
		x[0]);
	x[6] = vec3_add_vec3(vec3_mult(x[3], ((double)x_pos + 0.5) / VIEWPORT_WIDTH),
						 vec3_mult(x[4], ((double)y_pos + 0.5) / VIEWPORT_HEIGHT));
	x[7] = vec3_add_vec3(x[5], x[6]);
	return (vec3_normalize(vec3_sub_vec3(x[7], camera->view_point)));
}

int camera_move_view_point(int key, t_camera *camera)
{

	const double step = 0.5;
	const t_vector *ov = &camera->orientation_vec;
	t_vector *p;
	double degrees;
	int operation;

	operation = 1;
	p = &camera->view_point;
	if (key == K_A || key == K_D)
	{
		degrees = atan2(ov->x, ov->z);
		if (key == K_D)
		{
			p->x += step * cos(degrees);
			p->z -= step * sin(degrees);
		}
		else
		{
			p->x -= step * cos(degrees);
			p->z += step * sin(degrees);
		}
	}
	else if (key == K_W || key == K_S)
	{
		if (key == K_S)
			operation = -1;
		p->x += operation * (step * ov->x);
		p->y += operation * (step * ov->y);
		p->z += operation * (step * ov->z);
	}
	return (key);
}

// TODO: up and down works wierdly xd
int camera_change_orientation_vector(int key, t_camera *camera)
{
	const double angle = 0.05;
	const t_vector *v = &camera->orientation_vec;
	t_vector rotated;
	double theta;

	if (key == K_AR_L || key == K_AR_R)
	{
		theta = angle;
		if (key == K_AR_L)
			theta = -angle;
		rotated.x = cos(theta) * v->x + sin(theta) * v->z;
		rotated.y = v->y;
		rotated.z = -sin(theta) * v->x + cos(theta) * v->z;
	}
	else
	{
		theta = -angle;
		if (key == K_AR_U)
			theta = angle;
		rotated.x = v->x;
		rotated.y = cos(theta) * v->y - sin(theta) * v->z;
		rotated.z = sin(theta) * v->y + cos(theta) * v->z;
	}

	camera->orientation_vec = vec3_normalize(rotated);
	return (key);
}

t_color camera_get_pixel_color(
	const t_camera *camera,
	const t_scene *scene,
	int x, int y)
{
	t_vector ray_direction;
	t_ray ray;

	ray_direction = camera_calculate_ray_direction(camera, y, x);
	ray = create_ray(camera->view_point, ray_direction, create_color(0, 0, 0), 0);
	return (ray_hit_tree(&ray, scene->tree, scene));
}

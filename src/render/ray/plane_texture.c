#include "ray_texture.h"

#include <math.h> /* fabs() | sin() | floor() | cos() */

static void get_plane_uv(
	double *u,
	double *v,
	const t_plane *plane,
	t_hit_record *rec)
{
	t_vector diff;
	t_vector tan;
	t_vector bitan;
	t_vector up;

	diff = vec3_sub_vec3(rec->intersection_p, plane->pos);
	up = create_vector(0, 1, 0);
	if (fabs(vec3_dot(up, plane->normal_vec)) > 0.999)
		up = create_vector(1, 0, 0);
	tan = vec3_normalize(vec3_cross(up, plane->normal_vec));
	bitan = vec3_normalize(vec3_cross(plane->normal_vec, tan));
	*u = (vec3_dot(diff, tan) / TEXTURE_SC) - floor(vec3_dot(diff, tan) / TEXTURE_SC);
	*v = (vec3_dot(diff, bitan) / TEXTURE_SC) - floor(vec3_dot(diff, bitan) / TEXTURE_SC);
}

static t_color get_color(t_texture *t, double u, double v, t_vector *bump)
{
	int x;
	int y;
	int color;

	x = (int)(u * t->width) % t->width;
	y = (int)(v * t->height) % t->height;
	if (x < 0)
		x += t->width;
	if (y < 0)
		y += t->height;
	color = t->pixels[y * t->width + x];
	bump->x = (((color >> 16) & 0xFF) / 255.0) * 2.0 - 1.0;
	bump->y = (((color >> 8) & 0xFF) / 255.0) * 2.0 - 1.0;
	bump->z = ((color & 0xFF) / 255.0) * 2.0 - 1.0;
	return (int_to_rgb(color));
}

t_color get_plane_color(
	const t_plane *plane,
	t_hit_record *rec)
{
	double u;
	double v;
	double angle;
	t_color color;
	t_vector bump;
	t_vector rot_axis;

	get_plane_uv(&u, &v, plane, rec);
	if (plane->check_board)
	{
		if (((int)floor(u * BOARD_SIZE) + (int)floor(v * BOARD_SIZE)) % 2 == 0)
			return (create_color(0, 0, 0));
		return (create_color(255, 255, 255));
	}
	color = get_color(plane->texture, u, v, &bump);
	bump = vec3_normalize(bump);
	rot_axis = vec3_normalize(vec3_cross(plane->normal_vec, bump));
	angle = acos(vec3_dot(plane->normal_vec, bump));
	rec->normal = vec3_add_vec3(vec3_add_vec3(vec3_mult(bump, cos(angle)),
											  vec3_mult(vec3_cross(rot_axis, bump), sin(angle))),
								vec3_mult(rot_axis, vec3_dot(rot_axis, bump) * (1 - cos(angle))));
	return (color);
}

#include "minirt.h"
#include "vector.h"
#include "color.h"
#include "scene.h"
#include "mlx.h"
#include <sys/time.h>

t_ray	ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.color = (t_color){0, 0, 0};
	return (ray);
}

bool	hit_sphere(t_sphere *spheres, t_ray *ray)
{
	t_sphere	*sphere;
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t;

	sphere = spheres;
	while (sphere)
	{
		oc = vec3_sub_vec3(sphere->vector, ray->origin);
		a = vec3_dot(ray->direction, ray->direction);
		b = -2.0 * vec3_dot(oc, ray->direction);
		c = vec3_dot(oc, oc) - (sphere->diameter / 2.0) * (sphere->diameter / 2.0);
		discriminant = b * b - 4 * a * c;
		if (discriminant >= 0.0)
		{
			t = (-b - sqrt(discriminant)) / (2.0 * a);
			if (t > 0.0)
			{
				ray->color = sphere->color;
				return (true);
			}
			t = (-b + sqrt(discriminant)) / (2.0 * a);
			if (t > 0.0)
			{
				ray->color = sphere->color;
				return (true);
			}
		}
		sphere = sphere->next;
	}
	return (false);
}

t_color	hit_checker(t_scene *scene, t_ray rray)
{
	if (hit_sphere(scene->spheres, &rray))
		return (rray.color);
	// check_plane(scene->planes, ray);
	// check_cylinder(scene->cylinders, ray);
	return (rray.color);
}

void	ray_tracing(t_scene *scene)
{
	int			i;
	int			j;
	t_vector	pixel_center;
	t_vector	direction;
	t_ray		rray;
	t_camera	*camera;
	t_viewport	viewport;

	camera = scene->camera;
	viewport = camera->viewport;
	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			pixel_center = vec3_add_vec3(viewport.first_pixel,
					vec3_add_vec3(vec3_mult(viewport.pdelta_x, j),
						vec3_mult(viewport.pdelta_y, i)));
			direction = vec3_sub_vec3(pixel_center, camera->view_point);
			rray = ray(camera->view_point, direction);
			rray.color = hit_checker(scene, rray);
			draw_pixel(scene, j++, i, rray.color);
		}
		i++;
	}
}

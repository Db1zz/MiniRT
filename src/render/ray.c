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

double	hit_sphere(t_sphere *spheres, t_ray *ray)
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
		c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
		discriminant = b * b - 4 * a * c;
		if (discriminant >= 0.0)
		{
			ray->color = sphere->color;
			return (-b - sqrt(discriminant)) / (2.0 * a);
		}
		sphere = sphere->next;
	}
	return (-1.0);
}

t_color ray_color(t_ray *r, double discriminant)
{
	t_vector	u_vec;
	t_vector	result;

	u_vec = vec3_add_vec3(r->origin, vec3_mult(r->direction, discriminant));
	u_vec = vec3_sub_vec3(u_vec, (t_vector){0, 0, -1});
	u_vec = vec3_normalize(u_vec);
	result = vec3_mult(vec3_add(u_vec, 1), 0.5);
	return ((t_color){result.x, result.y, result.z});
}

t_color	hit_checker(t_scene *scene, t_ray ray)
{
	double	discriminant;

	discriminant = hit_sphere(scene->spheres, &ray);
	if (discriminant > 0.0)
		return (ray_color(&ray, discriminant));
	// check_plane(scene->planes, ray);
	// check_cylinder(scene->cylinders, ray);
	return ((t_color){255, 0, 255});
}

void		ray_tracing(t_scene *scene)
{
	int			x;
	int			y;
	t_vector	pixel_center;
	t_vector	direction;
	t_ray		rray;
	t_camera	*camera;
	t_viewport	viewport;

	camera = scene->camera;
	viewport = camera->viewport;
	x = 0;
	while (x < WIN_HEIGHT)
	{
		y = 0;
		while (y < WIN_WIDTH)
		{
			pixel_center = vec3_add_vec3(viewport.first_pixel,
							vec3_add_vec3(
								vec3_mult(viewport.pdelta_x, y),
								vec3_mult(viewport.pdelta_y, x)));
			direction = vec3_sub_vec3(pixel_center, camera->view_point);
			rray = ray(camera->view_point, vec3_normalize(direction));
			rray.color = hit_checker(scene, rray);
			print_color(&rray.color);
			draw_pixel(scene, y++, x, rray.color);
		}
		x++;
	}
}

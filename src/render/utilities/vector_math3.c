#include "vector.h"
#include "minirt_math.h"
#include <math.h>

double	vec3_lenght_squared(const t_vector *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

double	vec3_lenght(const t_vector *v)
{
	return (sqrt(vec3_lenght_squared(v)));
}

t_vector	vec3_random(void)
{
	return (create_vector(random_double(), random_double(), random_double()));
}

t_vector	vec3_random_range(double min, double max)
{
	return (create_vector(
				random_double_range(min, max),
				random_double_range(min, max),
				random_double_range(min, max)));
}

t_vector		vec3_random_unit_vec(void)
{
	const double	epsilon = 1e-4;
	t_vector		random_vec;
	double			vec_lenght;

	while (true)
	{
		random_vec = vec3_random_range(-1, 1);
		vec_lenght = vec3_lenght_squared(&random_vec);
		if (epsilon < vec_lenght && vec_lenght <= 1)
			return (vec3_div(random_vec, sqrt(vec_lenght)));
	}
}

t_vector	vec3_random_on_hemisphere(const t_vector *sphere_normal_vec)
{
	double		dot_product;
	t_vector	random_unit_vec;

	random_unit_vec = vec3_random_unit_vec();
	dot_product = vec3_dot(random_unit_vec, *sphere_normal_vec);
	if (dot_product > 0.0)
		return (random_unit_vec);
	else
		return (vec3_invert(&random_unit_vec));
}

#include "vector.h"
#include "minirt.h"
#include "utils.h"
#include <math.h>

t_vector	vec3_div_vec3(t_vector v1, t_vector v2)
{
	return (create_vector(div_c(v1.x,v2.x),
						div_c(v1.y, v2.y),
						div_c(v1.z,v2.z)));
}

t_vector	vec3_mult_vec3(t_vector v1, t_vector v2)
{
	return (create_vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

t_vector	vec3_sub_vec3(t_vector v1, t_vector v2)
{
	return (create_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector	vec3_add_vec3(t_vector v1, t_vector v2)
{
	return (create_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	vec3_normalize(t_vector vector)
{
	double	mag;

	mag = vec3_length(vector);
	if (mag == 0)
		return (vector);
	return (create_vector(vector.x / mag, vector.y / mag, vector.z / mag));
}

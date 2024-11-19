#include "vector.h"
#include <math.h>	

t_vector	vec3_div_vec3(t_vector v1, t_vector v2)
{
	v1.x = v1.x / v2.x;
	v1.y = v1.y / v2.y;
	v1.z = v1.z / v2.z;
	return (v1);
}

t_vector	vec3_mult_vec3(t_vector v1, t_vector v2)
{
	v1.x = v1.x * v2.x;
	v1.y = v1.y * v2.y;
	v1.z = v1.z * v2.z;
	return (v1);
}

t_vector	vec3_sub_vec3(t_vector v1, t_vector v2)
{
	v1.x = v1.x - v2.x;
	v1.y = v1.y - v2.y;
	v1.z = v1.z - v2.z;
	return (v1);
}

t_vector	vec3_add_vec3(t_vector v1, t_vector v2)
{
	v1.x = v1.x + v2.x;
	v1.y = v1.y + v2.y;
	v1.z = v1.z + v2.z;
	return (v1);
}

t_vector	vec3_normalize(t_vector vector)
{
	double	magnitude;

	magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	vector.x = vector.x / magnitude;
	vector.y = vector.y / magnitude;
	vector.z = vector.z / magnitude;
	return (vector);
}

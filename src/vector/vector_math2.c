#include "vector.h"

t_vector	vec3_div(t_vector vector, double val)
{
	vector.x = vector.x / val;		
	vector.y = vector.y / val;
	vector.z = vector.z / val;
	return (vector);
}

t_vector	vec3_mult(t_vector vector, double val)
{
	vector.x = vector.x * val;
	vector.y = vector.y * val;
	vector.z = vector.z * val;
	return (vector);
}

t_vector	vec3_sub(t_vector vector, double val)
{
	vector.x = vector.x - val;
	vector.y = vector.y - val;
	vector.z = vector.z - val;
	return (vector);
}

t_vector	vec3_add(t_vector vector, double val)
{
	vector.x = vector.x + val;
	vector.y = vector.y + val;
	vector.z = vector.z + val;
	return (vector);
}

double	vec3_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

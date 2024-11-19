#include "vector.h"

t_vector	vec3_div(t_vector vector, float val)
{
	vector.x = vector.x / val;		
	vector.y = vector.y / val;
	vector.z = vector.z / val;
	return (vector);
}

t_vector	vec3_mult(t_vector vector, float val)
{
	vector.x = vector.x * val;
	vector.y = vector.y * val;
	vector.z = vector.z * val;
	return (vector);
}

t_vector	vec3_sub(t_vector vector, float val)
{
	vector.x = vector.x - val;
	vector.y = vector.y - val;
	vector.z = vector.z - val;
	return (vector);
}

t_vector	vec3_add(t_vector vector, float val)
{
	vector.x = vector.x + val;
	vector.y = vector.y + val;
	vector.z = vector.z + val;
	return (vector);
}

#include "vector.h"
#include <math.h>

double	vec3_lenght_squared(const t_vector *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

double	vec3_lenght(const t_vector *v)
{
	return (sqrt(vec3_lenght_squared(v)));
}
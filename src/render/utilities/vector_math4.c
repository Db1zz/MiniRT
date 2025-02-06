#include "vector.h"

t_vector	vec3_cross(t_vector a, t_vector b)
{
    return (create_vector(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x 
    ));
}

t_vector    vec3_negate(t_vector a)
{
    return (create_vector(-a.x, -a.y, -a.z));
}

double	vec3_distance(t_vector a, t_vector b)
{
	double	x;

	x = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (x);
}
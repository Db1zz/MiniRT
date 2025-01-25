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

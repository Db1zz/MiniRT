#ifndef VECTOR_H
# define VECTOR_H

#include "ft_error.h"

# define VECTOR_MAX_SIZE 3

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

t_error		set_vector(t_vector *vector, float x, float y, float z);
t_error		str_to_vector(t_vector *vector, const char *vector_str);
t_vector	vec3_div_vec3(t_vector v1, t_vector v2);
t_vector	vec3_mult_vec3(t_vector v1, t_vector v2);
t_vector	vec3_sub_vec3(t_vector v1, t_vector v2);
t_vector	vec3_add_vec3(t_vector v1, t_vector v2);
t_vector	vec3_div(t_vector vector, float val);
t_vector	vec3_mult(t_vector vector, float val);
t_vector	vec3_sub(t_vector vector, float val);
t_vector	vec3_add(t_vector vector, float val);
t_vector	vec3_normalize(t_vector vector);

#endif // VECTOR_H
#ifndef VECTOR_H
# define VECTOR_H

#include "ft_error.h"
#include "color.h"

# define VECTOR_MAX_SIZE 3

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_error		set_vector(t_vector *vector, double x, double y, double z);
t_vector	get_random_vector_offset(void);
t_error		str_to_vector(t_vector *vector, const char *vector_str);
t_vector	vec3_div_vec3(t_vector v1, t_vector v2);
t_vector	vec3_mult_vec3(t_vector v1, t_vector v2);
t_vector	vec3_sub_vec3(t_vector v1, t_vector v2);
t_vector	vec3_add_vec3(t_vector v1, t_vector v2);
t_vector	vec3_div(t_vector vector, double val);
t_vector	vec3_mult(t_vector vector, double val);
t_vector	vec3_sub(t_vector vector, double val);
t_vector	vec3_add(t_vector vector, double val);
t_vector	vec3_normalize(t_vector vector);
double		vec3_dot(t_vector v1, t_vector v2);
double		vec3_lenght_squared(const t_vector *v);
double		vec3_lenght(const t_vector *v);
// debug functions
void	print_vec3(t_vector *vec);

#endif // VECTOR_H
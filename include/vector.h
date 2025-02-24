#ifndef VECTOR_H
# define VECTOR_H

#include "ft_error.h"
#include "color.h"
#include <math.h>
#include <stdio.h>

# define VECTOR_MAX_SIZE 3
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	create_vector(double x, double y, double z);
t_vector	vec3_invert(const t_vector *vec);
t_error		set_vector(t_vector *vector, double x, double y, double z);
t_vector	get_random_vector_offset(void);
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
double		vec3_length_squared(t_vector v);
double		vec3_length(t_vector v);
t_vector	vec3_random(void);
t_vector	vec3_random_range(double min, double max);
t_vector	vec3_random_unit_vec(void);
t_vector	vec3_random_on_hemisphere(const t_vector *sphere_normal_vec);
t_vector	vec3_cross(t_vector a, t_vector b);
t_vector    vec3_negate(t_vector a);
double		vec3_distance(t_vector a, t_vector b);
t_vector    vec3_abs(t_vector a);


// debug functions
void	print_vec3(t_vector *vec);

#endif // VECTOR_H

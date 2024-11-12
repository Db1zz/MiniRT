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

t_error	set_vector(t_vector *vector, float x, float y, float z);
t_error	str_to_vector(t_vector *vector, const char *vector_str);

#endif // VECTOR_H
#include "vector.h"
#include "minirt_math.h"
#include "minirt.h"
#include "libft.h"
#include <stdio.h>

t_vector	create_vector(double x, double y, double z)
{
	return ((t_vector){x, y, z});
}

t_vector	vec3_invert(const t_vector *vec)
{
	return (create_vector(-vec->x, -vec->y, -vec->z));
}

t_error	set_vector(t_vector *vector, double x, double y, double z)
{
	if (!vector)
		return (ERR_NULL_PARAMETER);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (ERR_NO_ERROR);
}

t_vector	get_random_vector_offset(void)
{
	return (create_vector(random_double() - 0.5, random_double() - 0.5, 0));
}

void	print_vec3(t_vector *vec)
{
	printf("Vector: [%f, %f, %f]\n", vec->x, vec->y, vec->z);
}

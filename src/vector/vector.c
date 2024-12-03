#include "vector.h"
#include "minirt_math.h"
#include "minirt.h"
#include "libft.h"

t_vector	vec3_invert(const t_vector *vec)
{
	return ((t_vector){-vec->x, -vec->y, -vec->z});
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
	return ((t_vector){random_double() - 0.5, random_double() - 0.5, 0});
}

t_error	str_to_vector(t_vector *vector, const char *vector_str)
{
	t_error	errorn;
	char	**data;

	if (!vector || !vector_str)
		return (ERR_NULL_PARAMETER);
	errorn = ERR_NO_ERROR;
	data = ft_split(vector_str, ',');
	if (!data)
		return (ERR_SPLIT_FAILED);
	if (!check_str_numbers(data, VECTOR_MAX_SIZE))
		errorn = ERR_STRING_IS_NOT_NUM;
	if (!errorn)
		set_vector(vector, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
	free_2dmatrix(data);
	return (errorn);
}

void	print_vec3(t_vector *vec)
{
	printf("Vector: [%f, %f, %f]\n", vec->x, vec->y, vec->z);
}

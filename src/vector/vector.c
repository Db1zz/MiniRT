#include "libft.h"
#include "vector.h"
#include "minirt.h"

t_error	set_vector(t_vector *vector, float x, float y, float z)
{
	if (!vector)
		return (ERR_NULL_PARAMETER);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (ERR_NO_ERROR);
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

double	vec3_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

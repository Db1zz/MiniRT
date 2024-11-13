#include "parser.h"

t_error	normalize_vector(t_vector *vector)
{
	double	magnitude;

	if (!vector)
		return (ERR_NULL_PARAMETER);
	magnitude = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	vector->x = vector->x / magnitude;
	vector->y = vector->y / magnitude;
	vector->z = vector->z / magnitude;
	return (ERR_NO_ERROR);
}

/*
	THIS IS THE BEST GENERIC FUNCTION IN MY LIFE
*/
void	shape_add_back(void	**shape_list, void	*shape)
{
	t_sphere	*temp;

	if (*(t_sphere **)shape_list == NULL)
		*(t_sphere **)shape_list = (t_sphere *)shape;
	temp = *(t_sphere **)shape_list;
	while (temp->next)
		temp = temp->next;
	temp->next = (t_sphere *)shape;
}

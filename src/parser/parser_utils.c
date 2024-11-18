#include "parser.h"
#include "mlx.h"
#include <math.h>

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
	{
		*(t_sphere **)shape_list = (t_sphere *)shape;
		return ;
	}
	temp = *(t_sphere **)shape_list;
	while (temp->next)
		temp = temp->next;
	temp->next = (t_sphere *)shape;
}

void	free_list(void *list)
{
	t_sphere *tmp;
	t_sphere *to_free;

	if (!list)
		return ;
	tmp = (t_sphere *)list;
	while (tmp) {
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
}

void	free_scene(t_scene **scene)
{
	if (!scene || !*scene)
		return ;
	free_list((void *)(*scene)->spheres);
	free_list((void *)(*scene)->cylinders);
	free_list((void *)(*scene)->planes);
	if ((*scene)->light)
		free((*scene)->light);
	if ((*scene)->amb_light)
		free((*scene)->amb_light);
	if ((*scene)->camera)
		free((*scene)->camera);
	if ((*scene)->win)
		mlx_destroy_window((*scene)->mlx, (*scene)->win);
	if ((*scene)->mlx)
	{
		mlx_destroy_display((*scene)->mlx);
		free((*scene)->mlx);
	}
	free(*scene);
	*scene = NULL;
}
#include "minirt.h"

void	free_2dmatrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

bool	is_string_number(char *line)
{
	int	i;

	if (line == NULL)
	{
		printf("Error in %s: line == NULL", __func__);
		return (false);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+'
				&& line[i] != '.' && line[i])
			return (false);
		i++;
	}
	return (true);
}

bool	check_str_numbers(char **numbers, int expected_size)
{
	int	i;

	if (numbers == NULL)
		return (false);
	i = 0;
	while (numbers[i] != NULL)
	{
		if (i > expected_size || !is_string_number(numbers[i]))
			return (false);
		i++;
	}
	if (i == expected_size)
		return (true);
	return (false);
}

size_t	get_2dmatrix_size(char **matrix)
{
	size_t	size;

	if (matrix == NULL)
		return (0);
	size = 0;
	while (matrix[size])
		size++;
	return (size);
}

void	free_scene(t_scene **scene)
{
	if (!scene || !*scene)
		return ;
	free_object_list(&(*scene)->objects);
	if ((*scene)->camera)
		free((*scene)->camera);
	if ((*scene)->win)
		mlx_destroy_window((*scene)->mlx, (*scene)->win);
	if ((*scene)->mlx)
	{
		#ifndef __APPLE__	// Temp macro
			mlx_destroy_display((*scene)->mlx);
		#endif	// __APPLE__
		free((*scene)->mlx);
	}
	free(*scene);
	*scene = NULL;
}

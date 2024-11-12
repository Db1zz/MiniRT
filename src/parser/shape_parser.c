#include "parser.h"
#include "minirt.h"

int	parse_sphere(t_scene *scene, const char **line_data)
{
	int			status;
	t_sphere	*sphere;

	status = 0;
	sphere = ft_malloc(sizeof(t_sphere));
	if (!sphere)
		return (-1);
	if (str_to_vector(&sphere->vector, line_data[1]))
		status = -1;
	if (!status && is_string_number(line_data[2]))
		sphere->diameter = ft_atof(line_data[2]);
	else
		status = -1;
	if (!status && str_to_color(&sphere->color, line_data[3]))
		status = -1;
	if (!status)
		free(sphere);
	else
		// TODO: add sphere to the list in scene->sphere
	return (status);
}

int	parse_cylinder(t_scene *scene, const char **line_data)
{
	int			status;
	t_cylinder	*cylinder;

	status = 0;
	cylinder = ft_malloc(sizeof(cylinder));
	if (!cylinder)
		return (-1);
	if (str_to_vector(&cylinder->vector, line_data[1]))
		status = -1;
	else if (str_to_vector(&cylinder->axis, line_data[2]))
		status = -1;
	else if (is_string_number(line_data[3]) && is_string_number(line_data[4]))
	{
		cylinder->diameter = ft_atof(line_data[3]);
		cylinder->height = ft_atof(line_data[4]);
		normalize_vector(&cylinder->axis);
	}
	else
		status = -1;
	if (!status && str_to_color(&cylinder->color, line_data[5]))
		status = -1;
	if (!status)
		free(cylinder);
	else
		// TODO: add cylinder to the list in scene->cylinders
	return (status);
}

void	parse_plane(t_scene *scene, char **line_data)
{
	int		status;
	t_plane	*plane;

	status = 0;
	plane = ft_malloc(sizeof(plane));
	if (!plane)
		return (-1);
	if (str_to_vector(&plane->vector, line_data[1]))
		status = -1;
	else if (str_to_vector((&plane->axis), line_data[2]))
		status = -1;
	else if (str_to_color((&plane->color), line_data[3]))
		status = -1;
	else if (!normalize_vector(&plane->axis)
			|| !normalize_vector(&plane->vector))
		status = -1;
	if (status)
		free(plane);
	else
		// TODO: add plane to the list in scene->plane
	return (status);	
}

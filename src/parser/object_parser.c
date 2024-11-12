#include "parser.h"
#include "minirt.h"

void	parse_light(t_scene *scene, const char **line_data)
{
	int		status;
	t_light	*light;

	status = 0;
	light = ft_malloc(sizeof(light));
	if (!light)
		return (-1);
	if (str_to_vector(&light->vector, line_data[1]))
		status = -1;
	else if (is_string_number(line_data[2]))
	{
		light->ratio = ft_atof(line_data[2]);
		if (light->ratio < RATIO_MIN || light->ratio > RATIO_MAX)
		{
			printf("Error in %s: light->ratio should be in range [0, 1]\n",
						__func__);
			status = -1;
		}
	}
	else
		status = -1;
	if (!status && str_to_color(&light->color, line_data[3]))
		status = -1;
	if (status)
		free(light);
	else
		// TODO: add this to the scene var
	return (status);
}

void	parse_ambient(t_scene *scene, const char **line_data)
{
	int				status;
	t_amb_lighting	*amb_lighting;

	status = 0;
	amb_lighting = ft_malloc(sizeof(t_amb_lighting));
	if (!amb_lighting)
		return (-1);
	amb_lighting->ratio = ft_atof(line_data[1]);
	if (!is_string_number(line_data[1]))
		status = -1;
	else if (amb_lighting->ratio < RATIO_MIN || amb_lighting->ratio > RATIO_MAX)
	{
		printf("Error in %s: light->ratio should be in range [%d, %d]\n",
					__func__, RATIO_MIN, RATIO_MAX);
		status = -1;
	}
	else if (str_to_color(&amb_lighting->color, line_data[2]))
		status = -1;
	if (status)
		free(amb_lighting);
	else
		// TODO: add this)
	return (status);
}

int	parse_camera(t_scene *scene, const char **line_data)
{
	int			status;
	t_camera	*camera;
	
	status = 0;
	camera = ft_malloc(sizeof(t_camera));
	if (camera)
		return (-1);
	if (str_to_vector(&camera->view_point, line_data[1]))
		status = -1;
	else if (str_to_vector(&camera->orientation_vec, line_data[2]))
		status = -1;
	camera->fov = ft_atoi(line_data[3]);
	if (!status && !is_string_number(line_data[3]))
		status = -1;
	else if (!status && (camera->fov < FOV_MIN || camera->fov > FOV_MAX))
	{
		printf("Error in %s: camera->fov should be in range [%d, %d]\n",
					__func__, FOV_MIN, FOV_MAX);
		status = -1;
	}
	if (status)
		free(camera);
	else
		// TODO: add this)
	return (status);
}

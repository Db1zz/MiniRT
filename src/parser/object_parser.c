#include "parser.h"
#include "minirt.h"

t_error	parse_light(t_scene *scene, const char **line_data)
{
	t_error	errorn;
	t_light	*light;

	errorn = ERR_NO_ERROR;
	light = malloc(sizeof(light));
	if (!light)
		return (ERR_MALLOC_FAILED);
	if (str_to_vector(&light->vector, line_data[1]))
		errorn = ERR_TYPE_CONVERSION_FAILED;
	else if (is_string_number(line_data[2]))
	{
		light->ratio = ft_atof(line_data[2]);
		if (light->ratio < RATIO_MIN || light->ratio > RATIO_MAX)
			errorn = ERR_RATIO_RANGE_ERROR;
	}
	else
		errorn = ERR_TYPE_CONVERSION_FAILED;
	if (!errorn && str_to_color(&light->color, line_data[3]))
		errorn = ERR_TYPE_CONVERSION_FAILED;
	if (errorn)
		free(light);
	else
		// TODO: add this to the scene var
	return (errorn);
}

t_error	parse_ambient(t_scene *scene, const char **line_data)
{
	t_error			errorn;
	t_amb_lighting	*amb_lighting;

	errorn = ERR_NO_ERROR;
	amb_lighting = malloc(sizeof(t_amb_lighting));
	if (!amb_lighting)
		return (ERR_MALLOC_FAILED);
	amb_lighting->ratio = ft_atof(line_data[1]);
	if (!is_string_number(line_data[1]))
		errorn = ERR_TYPE_CONVERSION_FAILED;
	else if (amb_lighting->ratio < RATIO_MIN || amb_lighting->ratio > RATIO_MAX)
		errorn = ERR_RATIO_RANGE_ERROR;
	else if (str_to_color(&amb_lighting->color, line_data[2]))
		errorn = ERR_TYPE_CONVERSION_FAILED;
	if (errorn)
		free(amb_lighting);
	else
		// TODO: add this)
	return (errorn);
}

t_error	parse_camera(t_scene *scene, const char **line_data)
{
	t_error		errorn;
	t_camera	*camera;
	
	errorn = ERR_NO_ERROR;
	camera = malloc(sizeof(t_camera));
	if (camera)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&camera->view_point, line_data[1]);
	if (!errorn)
		errorn = str_to_vector(&camera->orientation_vec, line_data[2]);
	if (!errorn && !is_string_number(line_data[3]))
	{
		camera->fov = ft_atoi(line_data[3]);
		errorn = ERR_ATOI_FAILED;
	}
	else if (!errorn && (camera->fov < FOV_MIN || camera->fov > FOV_MAX))
		errorn = ERR_INCORRECT_FOV_VALUE;
	if (errorn)
		free(camera);
	else
		// TODO: add this)
	return (errorn);
}

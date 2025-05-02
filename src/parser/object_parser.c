/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:12 by gonische          #+#    #+#             */
/*   Updated: 2025/04/08 15:58:00 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "parser.h"
#include "object.h"
#include "light.h"
#include "utils.h"
#include "libft.h"

#ifndef BONUS

void	parse_light(t_scene *scene, char **line_data)
{
	t_light	*light;

	if (scene->lights_size > 0)
		return (set_error(&scene->error, ERR_MULTIPLE_OBJECTS_INSTANCES, __func__));
	light = rt_calloc(1, sizeof(t_light), scene);
	if (!light)
		return ;
	str_to_vector(&light->pos, line_data[1], false, scene);
	light->ratio = rt_atof(line_data[2], scene);
	if (light->ratio < RATIO_MIN || light->ratio > RATIO_MAX)
		set_error(&scene->error, ERR_RATIO_RANGE_ERROR, __func__);
	str_to_color(&light->color, line_data[3], scene);
	add_object_to_array(light, E_LIGHT, 
		scene->lights, &scene->lights_size);
}
#else

void	parse_light(t_scene *scene, char **line_data)
{
	t_light	*light;

	if (scene->lights_size > SCENE_LIGHTS_LIMIT)
		return (set_error(&scene->error, ERR_OBJECTS_AMOUNT_EXCEED_LIMITS, __func__));
	light = rt_calloc(1, sizeof(t_light), scene);
	if (!light)
		return ;
	str_to_vector(&light->pos, line_data[1], false, scene);
	light->ratio = rt_atof(line_data[2], scene);
	if (light->ratio < RATIO_MIN || light->ratio > RATIO_MAX)
		set_error(&scene->error, ERR_RATIO_RANGE_ERROR, __func__);
	str_to_color(&light->color, line_data[3], scene);
	add_object_to_array(light, E_LIGHT, 
		scene->lights, &scene->lights_size);
}
#endif

void	parse_ambient(t_scene *scene, char **line_data)
{
	t_amb_lighting	*amb_lighting;

	if (scene->ambient_light_size > 0)
		return (set_error(&scene->error, ERR_MULTIPLE_OBJECTS_INSTANCES,__func__));
	amb_lighting = rt_calloc(1, sizeof(t_amb_lighting), scene);
	if (!amb_lighting)
		return ;
	amb_lighting->ratio = rt_atof(line_data[1], scene);
	if (amb_lighting->ratio < RATIO_MIN || amb_lighting->ratio > RATIO_MAX)
		set_error(&scene->error, ERR_RATIO_RANGE_ERROR, __func__);
	else
		str_to_color(&amb_lighting->color, line_data[2], scene);
	add_object_to_array(amb_lighting, E_AMBIENT_LIGHT, 
		scene->ambient_light, &scene->ambient_light_size);
}

void	parse_camera(t_scene *scene, char **line_data)
{
	t_camera	*camera;

	if (scene->camera != NULL)
		return (set_error(&scene->error, ERR_MULTIPLE_OBJECTS_INSTANCES, __func__));
	camera = rt_calloc(1, sizeof(t_camera), scene);
	if (!camera)
		return ;
	str_to_vector(&camera->view_point, line_data[1], false, scene);
	str_to_vector(&camera->orientation_vec, line_data[2], false, scene);
	if (is_string_number(line_data[3], scene))
		camera->fov = ft_atoi(line_data[3]);
	if (camera->fov < CAMERA_FOV_MIN || camera->fov > CAMERA_FOV_MAX)
		set_error(&scene->error, ERR_INCORRECT_FOV_VALUE, __func__);
	scene->camera = camera;
}

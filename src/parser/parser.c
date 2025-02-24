/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:41 by gonische          #+#    #+#             */
/*   Updated: 2025/02/24 16:38:11 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "libft.h"
#include "object.h"
#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

static void	line_parser(t_scene *scene, char **line_data)
{
	if (ft_strcmp("sp", line_data[0]) == 0)
		parse_sphere(scene, line_data);
	else if (ft_strcmp("pl", line_data[0]) == 0)
		parse_plane(scene, line_data);
	else if (ft_strcmp("cy", line_data[0]) == 0)
		parse_cylinder(scene, line_data);
	else if (ft_strcmp("cn", line_data[0]) == 0)
		parse_cone(scene, line_data);
	else if (ft_strcmp("A", line_data[0]) == 0)
		parse_ambient(scene, line_data);
	else if (ft_strcmp("L", line_data[0]) == 0)
		parse_light(scene, line_data);
	else if (ft_strcmp("C", line_data[0]) == 0)
		 parse_camera(scene, line_data);
	else if (ft_strcmp("hy", line_data[0]) == 0)
		parse_gyper(scene, line_data);
	else if (line_data[0][0] == '#')
		return ;
	else
		scene->error = ERR_UNKNOWN_OBJECT_SPECIFIER;
}

void	scene_add_object(void *data, t_object_type type, t_scene *scene)
{
	t_object_list	*new_object;
	t_object_list	**object_list;

	if (!data || !scene)
	{
		scene->error = ERR_NULL_PARAMETER;
		return ;
	}
	new_object = alloc_new_object(data, type, NULL);
	if (type == E_LIGHT)
		object_list = &scene->lights;
	else if (type == E_AMBIENT_LIGHT)
		object_list = &scene->ambient_lightings;
	else
		object_list = &scene->objects;
	object_add_back(new_object, object_list);
}

static void	scene_parser(t_scene *scene, int scene_fd)
{
	char	*line;
	char	**splitted_line;

	while (scene->error == ERR_NO_ERROR)
	{
		line = get_next_line(scene_fd);
		if (!line)
			break ;
		splitted_line = ft_split(line, ' ');
		if (splitted_line && splitted_line[0][0] != '\n')
		{
			line_parser(scene, splitted_line);
			free_2dmatrix(splitted_line);
		}
		free(line);
	}
	if (!scene->camera)
		set_error(&scene->error, ERR_CAMERA_NOT_FOUND);
}

t_scene	*parse_input(int argc, char **argv)
{
	int		fd;
	t_scene	*scene;

	if (argc != 2)
		return (ft_perror(ERR_ARGC_ERROR, __func__), NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_perror(ERR_FAILED_TO_OPEN_FILE, __func__), NULL);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (ft_perror(ERR_MALLOC_FAILED, __func__), NULL);
	if (scene->error == ERR_NO_ERROR)
		scene_parser(scene, fd);
	if (scene->error)
		(ft_perror(scene->error, __func__), free_scene(&scene));
	close(fd);
	return (scene);
}

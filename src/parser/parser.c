/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:41 by gonische          #+#    #+#             */
/*   Updated: 2025/05/05 13:54:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "libft.h"
#include "object.h"
#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

static void line_parser(t_scene *scene, char **line_data)
{
	if (ft_strcmp("sp", line_data[0]) == 0)
		parse_sphere(scene, line_data);
	else if (ft_strcmp("pl", line_data[0]) == 0)
		parse_plane(scene, line_data);
	else if (ft_strcmp("cy", line_data[0]) == 0)
		parse_cylinder(scene, line_data);
	else if (ft_strcmp("hy", line_data[0]) == 0)
		parse_gyper(scene, line_data);
	else if (ft_strcmp("A", line_data[0]) == 0)
		parse_ambient(scene, line_data);
	else if (ft_strcmp("L", line_data[0]) == 0)
		parse_light(scene, line_data);
	else if (ft_strcmp("C", line_data[0]) == 0)
		parse_camera(scene, line_data);
	else if (line_data[0][0] == '#')
		return;
	else
		set_error(&scene->error, ERR_UNKNOWN_OBJECT_SPECIFIER, __func__);
}

static void scene_parser(t_scene *scene, int scene_fd)
{
	char *line;
	char **splitted_line;

	splitted_line = NULL;
	while (scene->error.errorn == ERR_NO_ERROR)
	{
		line = get_next_line(scene_fd);
		if (!line)
			break;
		splitted_line = ft_split(line, ' ');
		if (splitted_line && splitted_line[0][0] != '\n')
		{
			line_parser(scene, splitted_line);
			free_2dmatrix(splitted_line);
		} 
		else if (splitted_line)
		{
			free_2dmatrix(splitted_line);
			splitted_line = NULL;
		}
		free(line);
	}
	if (!scene->camera)
		set_error(&scene->error, ERR_CAMERA_NOT_FOUND, __func__);
}

t_error parse_input(t_scene *scene, int argc, char **argv)
{
	int fd;

	if (argc != 2)
		return (ft_perror(ERR_ARGC_ERROR, __func__), scene->error);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_perror(ERR_FAILED_TO_OPEN_FILE, __func__), scene->error);
	if (scene->error.errorn == ERR_NO_ERROR)
		scene_parser(scene, fd);
	if (scene->error.errorn)
		ft_display_error(&scene->error);
	close(fd);
	return (scene->error);
}

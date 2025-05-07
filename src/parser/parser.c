/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:41 by gonische          #+#    #+#             */
/*   Updated: 2025/05/07 15:27:46 by gonische         ###   ########.fr       */
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

static bool	validate_file_extension(const char *file_name, const char *extension)
{
	size_t	i;

	i = 0;
	if (!file_name || !extension)
		return (false);
	while (file_name[i] && file_name[i] != '.')
		++i;
	if (file_name[i] != '.')
		return (false);
	return (!ft_strcmp(file_name + i, extension));
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

t_error	parse_input(t_scene *scene, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (create_error(ERR_ARGC_ERROR, __func__));
	if (!validate_file_extension(argv[1], ".rt"))
		return (create_error(ERR_INVALID_FILE_EXTENSION, __func__));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (create_error(ERR_FAILED_TO_OPEN_FILE, __func__));
	if (scene->error.errorn == ERR_NO_ERROR)
		scene_parser(scene, fd);
	if (scene->error.errorn)
		return (close(fd), scene->error);
	close(fd);
	return (create_error(ERR_NO_ERROR, NULL));
}

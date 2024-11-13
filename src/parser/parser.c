#include "dependencies.h"
#include "parser.h"
#include "minirt.h"
#include <fcntl.h>
#include <unistd.h>

static t_error	line_parser(t_scene *scene, char **line_data)
{
	if (ft_strcmp("sp", line_data[0]) == 0)
		return (parse_sphere(scene, line_data));
	else if (ft_strcmp("pl", line_data[0]) == 0)
		return (parse_plane(scene, line_data));
	else if(ft_strcmp("cy", line_data[0]) == 0)
		return (parse_cylinder(scene, line_data));
	else if (ft_strcmp("A", line_data[0]) == 0)
		return (parse_ambient(scene, line_data));
	else if (ft_strcmp("L", line_data[0]) == 0)
		return (parse_light(scene, line_data));
	else if (ft_strcmp("C", line_data[0]) == 0)
		return (parse_camera(scene, line_data));
	else
		return (ERR_UNKNOWN_OBJECT_SPECIFIER);
}

t_error	scene_parser(t_scene *scene, int scene_fd)
{
	t_error	errorn;
	char	*line;
	char	**line_data;

	errorn = ERR_NO_ERROR;
	while (errorn == ERR_NO_ERROR)
	{
		line = get_next_line(scene_fd);
		if (!line)
			break ;
		line_data = ft_split(line_data, ' ');
		errorn = line_parser(scene, line_data);
		free_2dmatrix(line_data);
		free(line);
	}
	return (errorn);
}

t_scene	*parse_input(int argc, char **argv)
{
	t_error	errorn;
	int		fd;
	t_scene	*scene;

	if (argc != 2)
	{
		ft_perror(ERR_ARGC_ERROR, __func__);
		return (NULL);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_perror(ERR_FAILED_TO_OPEN_FILE, __func__);
		return (NULL);
	}
	scene = malloc(sizeof(t_scene));
	if (!scene)
		errorn = ERR_MALLOC_FAILED;
	if (errorn == ERR_NO_ERROR)
		errorn = scene_parser(scene, fd);
	if (errorn)
		(ft_perror(errorn, __func__), free(scene));
	close(fd);
	return (scene);
}

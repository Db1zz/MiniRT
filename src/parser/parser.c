#include "dependencies.h"
#include "object.h"
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

t_error	scene_add_object(void *data, t_object_type type, t_scene *scene)
{
	t_object_list	*new_object;

	if (!data || !scene)
		return (ERR_NULL_PARAMETER);
	new_object = alloc_new_object(data, type, NULL);
	object_add_back(new_object, &scene->objects);
	return (ERR_NO_ERROR);
}

t_error	scene_parser(t_scene *scene, int scene_fd)
{
	t_error	errorn;
	char	*line;
	char	**splitted_line;

	errorn = ERR_NO_ERROR;
	while (errorn == ERR_NO_ERROR)
	{
		line = get_next_line(scene_fd);
		if (!line)
			break ;
		splitted_line = ft_split(line, ' ');
		if (splitted_line && splitted_line[0][0] != '\n')
		{
			errorn = line_parser(scene, splitted_line);
			free_2dmatrix(splitted_line);
		}
		free(line);
	}
	return (errorn);
}

t_scene	*parse_input(int argc, char **argv)
{
	t_error			errorn;
	int				fd;
	t_scene			*scene;

	errorn = ERR_NO_ERROR;
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
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		errorn = ERR_MALLOC_FAILED;
	if (errorn == ERR_NO_ERROR)
		errorn = scene_parser(scene, fd);
	if (errorn)
		(ft_perror(errorn, __func__), free_scene(&scene));
	close(fd);
	return (scene);
}

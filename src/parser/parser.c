#include "dependencies.h"
#include "parser.h"
#include "minirt.h"
#include <fcntl.h>
#include <unistd.h>

void	line_parser(t_scene *scene, char **line_data)
{
	if (ft_strcmp("sp", line_data[0]) == 0)
		parse_sphere(scene, line_data);
	else if (ft_strcmp("pl", line_data[0]) == 0)
		parse_plane(scene, line_data);
	else if(ft_strcmp("cy", line_data[0]) == 0)
		parse_cylinder(scene, line_data);
	else if (ft_strcmp("A", line_data[0]) == 0)
		parse_ambient(scene, line_data);
	else if (ft_strcmp("L", line_data[0]) == 0)
		parse_light(scene, line_data);
	else if (ft_strcmp("C", line_data[0]) == 0)
		parse_camera(scene, line_data);
}

void	scene_parser(t_scene *scene, int scene_fd)
{
	char	*line;
	char	**line_data;

	while (true)
	{
		line = get_next_line(scene_fd);
		if (!line)
			break ;
		line_data = ft_split(line_data, ' ');
		line_parser(scene, line_data);
		free_2dmatrix(line_data);
		free(line);
	}
}

t_scene	*parse_input(int argc, char **argv)
{
	int		fd;
	t_scene	*scene;

	if (argc != 2)
	{
		printf("Error in %s: argc == %d expected 2", __func__, argc);
		return (NULL);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error in %s: failed to open file\n");
		return (NULL);
	}
	scene = malloc(sizeof(t_scene));
	scene_parser(scene, fd);
	/*
		1. Open .rt file, return NULL if open() fails
		2. Then separately parce each object. Objects which starts with captial letter
		should be parced only once, but for shapes we can use linked list?
		Basically we're generating SCENE struct which will hold
			Ambient lightning
			Camera
			Light source
			Sphere(linked list)
			Cylinder(linked list)
			Plane(linked list)
		and ofc each of these variables will be represented as structs which we're gonna to use to render scene.
	*/
	close(fd);
}

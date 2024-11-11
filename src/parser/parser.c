/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:43:44 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:28 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "parser.h"
#include "minirt.h"
#include <fcntl.h>
#include <unistd.h>

/*
	color_parser
	size_parser
	pos_parser
*/

/*
	Parser TODO:
	1. Rewrite this bullshit using modular structure.
	2. Add error handling for incorrect input.
*/

bool	parse_sphere(t_scene *scene, char **line_data)
{
	t_pos		pos;
	t_color		color;
	char		**data;
	bool		err_status;

	err_status = true;
	do
	{
		// if (!line_data[0] || !line_data[1] || !line_data[2])
		// 	break ;
		data = ft_split(line_data[1], ',');
		// if (!data[0] || !data[1] || !data[2])
		// 	break ;	
		set_pos(&pos, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		free_2dmatrix(data);		
		data = ft_split(line_data[2], ',');
		// if (!data[0] || !data[1] || !data[2])
		// 	break ;	
		set_color(&color, ft_atoi(data[0]), ft_atoi(data[1]), ft_atoi(data[2]));
		create_sphere(scene, &pos, &color, ft_atof(line_data[1]));
		err_status = false;
	}
	while (false);
	if (err_status)
		printf("Error in %s: incorrect input\n", __func__);
	return (err_status);
}



/*
	this function is completely bullshit but I will make it better lol
*/
bool	parse_cylinder(t_scene *scene, char **line_data)
{
	t_pos	pos; // Pos of the cylinder
	t_pos	u_axis; // unit vector
	t_color	color;
	char	**data;
	bool	err_status;
	
	err_status = true;
	do
	{
		// if (get_2dmatrix_size(line_data) != CYLINDER_ARGS)
		// 	break ;
		// parse cylinder pos
		data = ft_split(line_data[1], ',');
		// if (get_2dmatrix_size(data) != 3)
		// 	break ;
		set_pos(&pos, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		free_2dmatrix(data);
		
		// parse and normalize 3d vector of axis of cylinder in range [-1, 1]
		// check amount of data dumbass
		data = ft_split(line_data, ',');
		set_pos(&u_axis, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		free_2dmatrix(data);
		normalize_vector(&u_axis);
		// check amount of data dumbass
		data = ft_split(line_data[2], ',');
		set_color(&color, atoi(data[0]), atoi(data[1]), atoi(data[2]));
		create_cylinder(scene, &pos, &u_axis, ft_atof(line_data[3]),
					ft_atof(line_data[4]), &color);
		free_2dmatrix(data);
		err_status = false;
	} while(false);
	if (err_status)
		printf("Error in %s: incorrect input\n", __func__);
	return (err_status);
}

void	parse_plane(t_scene *scene, char **line_data)
{
	t_pos	pos;
	t_pos	u_vector;
	t_color	color;
	char	**data;
	double	magnitude;

	do
	{
		// x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
		data = ft_split(line_data[1], ',');
		set_pos(&pos,ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		free_2dmatrix(data);
		// 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
		data = ft_split(line_data[2], ',');
		set_pos(&u_vector, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		normalize_vector(&u_vector);
		free_2dmatrix(data);
		// R,G,B colors in range [0-255]: 0,0,225
		data = ft_split(line_data[3], ',');
		set_color(&color, ft_atoi(data[0]), ft_atoi(data[1]), ft_atoi(data[2]));
		create_plane(scene, &pos, &u_vector, &color);
		free_2dmatrix(data);
	} while (false);
}

void	parse_light(t_scene *scene, char **line_data)
{
	t_pos	pos;
	t_color	color;
	char	**data;
	double	ratio;

	do
	{
		// x,y,z coordinates of the light point: -40.0,50.0,0.0
		data = ft_split(line_data[1], ',');
		set_pos(&pos, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		free_2dmatrix(data);
		// the light brightness ratio in range [0.0,1.0]: 0.6
		ratio = ft_atof(line_data[2]);
		// (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
		data = ft_split(line_data[3], ',');
		set_color(&color, ft_atoi(data[0]), ft_atoi(data[1]), ft_atoi(data[2]));
		free_2dmatrix(data);
		create_light(scene, &pos, ratio, &color);
	}	while (false);
}

void	parse_ambient(t_scene *scene, char **line_data)
{
	t_color	color;
	double	ratio;
	char	**data;

	do
	{
		// ambient lighting ratio in range [0.0,1.0]: 0.2
		ratio = ft_atof(line_data[1]);
		// R,G,B colors in range [0-255]: 255, 255, 255
		data = ft_split(line_data[2], ',');
		set_color(&color, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		free_2dmatrix(data);
		create_amb_lightning(scene, ratio, &color);
	}	while (false);
}

void	parse_camera(t_scene *scene, char **line_data)
{
	t_pos	view_point;
	t_pos	orientation_vec;
	int		fov;
	char	**data;

	do
	{
		// ∗ x,y,z coordinates of the view point
		data = ft_split(line_data[1], ',');
		set_pos(&view_point, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		free_2dmatrix(data);
		// ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
		data = ft_split(line_data[2], ',');
		set_pos(&orientation_vec, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
		normalize_vector(&orientation_vec);
		free_2dmatrix(data);
		// ∗ FOV : Horizontal field of view in degrees in range [0,180]
		fov = ft_atoi(line_data[3]);
		create_camera(scene, &view_point, &orientation_vec, fov);
	}	while (false);
}


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
		and ofc each of these variables will be represented as structs which we're gonna to use to display shape.
	*/
	close(fd);
}

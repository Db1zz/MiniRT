/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:43:44 by gonische          #+#    #+#             */
/*   Updated: 2024/11/07 15:36:06 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "parser.h"

/* set return value */ void	*parse_input(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error in %s: argc == %d expected 2", __func__, argc);
		return (NULL);
	}
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
}

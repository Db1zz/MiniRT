/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:49:28 by gonische          #+#    #+#             */
/*   Updated: 2024/11/07 15:05:52 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
#define SHAPES_H

# include "color.h"
# include "pos.h"

typedef enum e_shape_type
{
	S_CYLINDER,
	S_SPHERE,
	S_PLANE
}	t_shape_type;

typedef struct s_shape_size
{
	int	height;
	int	width;
	int	diameter;
}	t_shape_size;

typedef struct s_sphere
{
	t_shape_size	size;
	t_pos			pos;
	t_color			color;
	t_sphere		*next;
}	t_sphere;

typedef struct s_plane
{
	t_pos	pos;
	t_pos	point;
	t_pos	axis;
	t_color	color;
	t_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_pos			pos;
	t_pos			axis;
	t_color			color;
	t_shape_size	size;
	t_cylinder		*next;
}	t_cylinder;

void	create_cylinder(/*params*/);
void	create_sphere(/*params*/);
void	create_plane(/*params*/);

#endif // SHAPES_H

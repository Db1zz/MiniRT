/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:49:28 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 23:13:59 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
#define SHAPES_H

# include "color.h"
# include "vector.h"

typedef enum e_shape_type
{
	S_CYLINDER,
	S_SPHERE,
	S_PLANE
}	t_shape_type;

typedef struct s_sphere
{
	float		diameter;
	t_vector	vector;
	t_color		color;
	t_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_vector	vector;
	t_vector	point;
	t_vector	axis;
	t_color	color;
	t_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vector		vector;
	t_vector		axis;
	t_color		color;
	float		diameter;
	float		height;
	t_cylinder	*next;
}	t_cylinder;

void	create_sphere(t_scene *scene, const t_vector *vector,
			const t_color *color, float diameter);
void	create_cylinder(t_scene *scene, const t_vector *vector,
			const t_vector *u_axis, float diameter, float height,
			const t_color *color);
void	create_plane(t_scene *scene, const t_vector *vector,
			const t_vector *u_vector, const t_color *color);

#endif // SHAPES_H

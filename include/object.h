/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:39:25 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 13:39:25 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h" /* t_vector */
# include "aabb.h" /* t_aabb */
# include "texture.h" /* t_texture */
# include "color.h" /* t_color */

# include <stdlib.h> /* size_t */

/*
	// ====================== Typedefs ====================== //
*/
typedef struct s_object	t_object;
typedef void			(*t_object_destructor)(t_object *);

/*
	typedef enum e_object_type

	The order of the enums are important, do not change it,
	because some functions are depend on it e.g ray_hit_shape().

	If new object is added, don't forget to update object_type_string function.
*/
typedef enum e_object_type
{
	E_SPHERE,
	E_CYLINDER,
	E_PLANE,
	E_GYPER,
	// Add new shape before this line
	E_LIGHT,
	E_AMBIENT_LIGHT,
	E_TOTAL_OBJECTS,
}	t_object_type;

typedef struct s_object
{
	t_aabb				box;
	void				*data;
	const char			*type_name;
	t_object_destructor	destructor; /* NULLABLE */
	t_object_type		type;
	size_t				id;
}	t_object;

// Typedefs

/*
	// ====================== Functions ====================== //
*/
t_object	*object_alloc(
				void *data,
				t_aabb box,
				t_object_type type,
				size_t id);

const char	*object_get_type_name(t_object_type type);

void		object_destroy_cylinder(t_object *cylinder_object);

void		object_destroy_plane(t_object *plane_object);

void		object_destroy(t_object **object);
// Functions

/*
	// ====================== Shapes ====================== //
*/
/* ====================== Sphere ======================*/
typedef struct s_sphere
{
	t_vector	pos;
	t_color		color;
	double		diameter;
	double		radius;
}	t_sphere;

t_aabb		compute_sphere_aabb(t_sphere *sphere);
//// Sphere

/* ====================== Cylinder ======================*/
typedef struct s_cylinder
{
	t_object	*caps;
	t_vector	pos;
	t_color		color;
	t_vector	axis;
	double		diameter;
	double		radius;
	double		height;
}	t_cylinder;

t_aabb		compute_cylinder_aabb(t_cylinder *cylinder);
//// Cylinder

/* ====================== Plane ======================*/
typedef struct s_plane
{
	t_vector	pos;
	t_color		color;
	t_vector	normal_vec;
	t_texture	*texture;
	bool		check_board;
}	t_plane;

t_aabb		compute_plane_aabb(void);
//// Plane

/* ====================== Hyperboloid ======================*/
typedef struct s_gyper
{
	t_vector	pos;
	t_vector	axis;
	t_vector	squish;
	t_color		color;
	double		diameter;
}	t_gyper;

t_aabb		compute_hyperboloid_aabb(void);
//// Hyperboloid
// Shapes

#endif // OBJECTS_H
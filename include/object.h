#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "texture.h"

/*
	Typedefs
*/
typedef enum e_object_type
{
	E_SPHERE,
	E_CYLINDER,
	E_PLANE,
	E_LIGHT,
	E_AMBIENT_LIGHT,
	E_CONE,
	E_GYPER,
	E_TOTAL_OBJECTS,
}	t_object_type;

typedef struct s_object_list
{
	void					*data;
	t_object_type			type;
	struct s_object_list	*next;
}	t_object_list;

/*
	Functions
*/
t_object_list	*alloc_new_object(
					void *data,
					t_object_type type,
					t_object_list *next);

void			object_add_back(
					t_object_list *new,
					t_object_list **list);

void			free_object(t_object_list **object);

void			free_object_list(t_object_list **list);

/*
	Objects
*/
typedef struct s_sphere
{
	t_vector		pos;
	t_color			color;
	double			diameter;
	double			radius;
}	t_sphere;

typedef struct s_plane
{
	t_vector	pos;
	t_color		color;
	t_vector	normal_vec;
}	t_plane;

typedef struct s_cylinder
{
	t_vector			pos;
	t_color				color;
	t_vector			axis;
	double				diameter;
	double				height;
}	t_cylinder;

typedef struct s_cone
{
	t_vector	pos;
	t_color		color;
	t_vector	axis;
	double		diameter;
	double		height;
}	t_cone;

typedef struct s_gyper
{
	t_vector	pos;
	t_vector	axis;
	t_vector	squish;
	t_color		color;
	double		diameter;
}	t_gyper;

#endif	// OBJECTS_H
//grisha was here
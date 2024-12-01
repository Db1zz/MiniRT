#ifndef OBJECTS_H
# define OBJECTS_H

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
	E_TOTAL_OBJECTS
}	t_object_type;

typedef	struct	s_object_list
{
	void					*data;
	t_object_type			type;
	struct s_object_list	*next;
}	t_object_list;

/*
	Functions
*/
t_object_list	*alloc_new_object(void *data, t_object_type type, t_object_list *next);
void			object_add_back(t_object_list *new, t_object_list **list);
void			free_object(t_object_list **object);
void			free_object_list(t_object_list **list);

/*
	Objects
*/
# include "light.h"

typedef struct s_sphere
{
	double			diameter;
	double			radius;
	t_vector		vector;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	t_vector		vector;
	t_vector		point;
	t_vector		axis;
	t_color			color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector			vector;
	t_vector			axis;
	t_color				color;
	double				diameter;
	double				height;
}	t_cylinder;

#endif	// OBJECTS_H
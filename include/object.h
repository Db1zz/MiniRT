#ifndef OBJECTS_H
# define OBJECTS_H

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
	void			*data;
	t_object_type	type;
	t_object_list	*next;
}	t_object_list;

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
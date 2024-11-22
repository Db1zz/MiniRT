#ifndef SHAPES_H
# define SHAPES_H

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
	struct s_sphere	*next;
	float			diameter;
	float			radius;
	t_vector		vector;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	struct s_plane	*next;
	t_vector		vector;
	t_vector		point;
	t_vector		axis;
	t_color			color;
}	t_plane;

typedef struct s_cylinder
{
	struct s_cylinder	*next;
	t_vector			vector;
	t_vector			axis;
	t_color				color;
	float				diameter;
	float				height;
}	t_cylinder;

#endif // SHAPES_H

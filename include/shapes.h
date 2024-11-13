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
	t_sphere	*next;
	float		diameter;
	t_vector	vector;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_plane		*next;
	t_vector	vector;
	t_vector	point;
	t_vector	axis;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_cylinder	*next;
	t_vector	vector;
	t_vector	axis;
	t_color		color;
	float		diameter;
	float		height;
}	t_cylinder;

void	create_sphere(t_scene *scene, const t_vector *vector,
			const t_color *color, float diameter);
void	create_cylinder(t_scene *scene, const t_vector *vector,
			const t_vector *u_axis, float diameter, float height,
			const t_color *color);
void	create_plane(t_scene *scene, const t_vector *vector,
			const t_vector *u_vector, const t_color *color);

#endif // SHAPES_H

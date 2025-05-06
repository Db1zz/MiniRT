#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "texture.h"
#include "aabb.h"

/*
	Typedefs
*/
typedef struct s_object t_object;
typedef void (*object_destructor)(t_object *);

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
	E_GYPER, // Add new Shape after this one, and move this line to the last shape.
	E_LIGHT,
	E_AMBIENT_LIGHT,
	E_TOTAL_OBJECTS,
} t_object_type;

typedef struct s_object
{
	t_aabb box;
	void *data;
	const char *type_name;
	object_destructor destructor; /* NULLABLE */
	t_object_type type;
	size_t id;
	
} t_object;


/*
	Functions
*/
t_object	*object_alloc(void *data, t_aabb box, t_object_type type, size_t id);
const char	*object_get_type_name(t_object_type type);
void		object_destroy_cylinder(t_object *cylinder_object);
void		object_destroy(t_object **object);

/*
	Objects
*/
typedef struct s_sphere
{
	t_vector pos;
	t_color color;
	double diameter;
	double radius;
} t_sphere;

typedef struct s_cylinder
{
	t_object *caps;
	t_vector pos;
	t_color color;
	t_vector axis;
	double diameter;
	double radius;
	double height;
} t_cylinder;

typedef struct s_plane
{
	t_vector	pos;
	t_color		color;
	t_vector	normal_vec;
	t_texture	*texture;
} t_plane;

typedef struct s_gyper
{
	t_vector pos;
	t_vector axis;
	t_vector squish;
	t_color color;
	double diameter;
} t_gyper;

#endif // OBJECTS_H
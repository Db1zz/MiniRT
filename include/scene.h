#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "shapes.h"
# include "light.h"

typedef struct s_scene
{
	/*camera*/
	/*ambient light*/
	/*light sources*/
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_scene;

#endif	// SCENE_H

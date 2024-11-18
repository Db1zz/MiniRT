#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "shapes.h"
# include "light.h"
# include "viewport.h"

typedef struct s_scene
{
	void			*win;
	void			*mlx;
	t_camera		*camera;
	t_amb_lighting	*amb_light;
	t_light			*light;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
}	t_scene;

void	free_scene(t_scene **scene);

#endif	// SCENE_H

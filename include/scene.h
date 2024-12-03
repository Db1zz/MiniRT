#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "light.h"
# include "object.h"
# include "viewport.h"

typedef struct s_scene
{
	void			*win;
	void			*mlx;
	bool			antialiasing;
	t_camera		*camera;
	t_object_list	*lights;
	t_object_list	*ambient_lightings;
	t_object_list	*objects;
}	t_scene;

void	free_scene(t_scene **scene);

#endif	// SCENE_H

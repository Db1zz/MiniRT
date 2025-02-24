#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "object.h"
# include "ft_error.h"

typedef struct s_scene
{
	void			*win;
	void			*mlx;
	t_error			error;
	t_camera		*camera;
	t_object_list	*lights;
	t_object_list	*ambient_lightings;
	t_object_list	*objects;
	bool			antialiasing;
}	t_scene;

void	free_scene(t_scene **scene);

#endif	// SCENE_H

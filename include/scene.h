#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "object.h"
# include "ft_error.h"

# define SCENE_LIGHTS_LIMIT 10
# define SCENE_AMBIENT_LIGHTNING_LIMIT 10
# define SCENE_OBJECTS_LIMIT 1024
# define SCENE_ANTIALIASING_SAMPLES 10

typedef struct s_scene
{
	void		*win;
	void		*mlx;
	t_camera	*camera;
	t_object	**lights; // [SCENE_LIGHTS_LIMIT + 1];
	t_object	**ambient_light; // [SCENE_AMBIENT_LIGHTNING_LIMIT + 1];
	t_object	**objects; // [SCENE_OBJECTS_LIMIT + 1];
	size_t		lights_size;
	size_t		ambient_light_size;
	size_t		objects_size;
	t_error		error;
}	t_scene;

t_scene	*scene_alloc(void);
void	free_scene(t_scene **scene);

#endif	// SCENE_H

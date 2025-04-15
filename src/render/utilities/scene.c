#include "scene.h"
#include "object.h"
#include "libft.h" // ft_calloc
#include "viewport.h" // update_viewport + viewport dimensions
#include "mlx.h" // mlx stuff
#include "xpm_render.h"

#include <stdlib.h>

t_scene	*scene_alloc(void)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	scene->objects = ft_calloc(SCENE_OBJECTS_LIMIT + 1, sizeof(t_object *));
	scene->lights = ft_calloc(SCENE_LIGHTS_LIMIT + 1, sizeof(t_object *));
	scene->ambient_light
		= ft_calloc(SCENE_AMBIENT_LIGHTNING_LIMIT + 1, sizeof(t_object *));
	return (scene);
}

static void	free_scene_objects(t_object **objects)
{
	int	i;

	i = 0;
	while (objects[i]) {
		free_object(&objects[i]);
		++i;
	}
}

void	free_scene(t_scene **scene)
{
	free_scene_objects((*scene)->ambient_light);
	free_scene_objects((*scene)->lights);
	free_scene_objects((*scene)->objects);
	if ((*scene)->camera)
		free((*scene)->camera);
	if ((*scene)->win)
		mlx_destroy_window((*scene)->mlx, (*scene)->win);
	if ((*scene)->mlx)
	{
		#ifndef __APPLE__	// Temp macro
			mlx_destroy_display((*scene)->mlx);
		#endif	// __APPLE__
		free((*scene)->mlx);
	}
	free(*scene);
	*scene = NULL;
}

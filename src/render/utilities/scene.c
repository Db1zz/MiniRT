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
	while (objects[i])
		free_object(&objects[i++]);
}

#ifdef __APPLE__
/*
	mlx is a cross-platform library they said))))))
*/
	void mlx_destroy_display(void *mlx)
	{
		(void)mlx;
	}

#endif // __APPLE__

void 	kill_free_threads(t_scene *scene)
{
	size_t	i;

	i = 0;
	ft_printf("Killing threads...\n");
	ft_printf("Waiting till each thread will be killed...\n");
	while (i < scene->threads_amount)
	{
		pthread_join(scene->threads_ctx[i].pt, NULL);
		++i;
	}
}

void free_scene(t_scene **scene)
{
	free_scene_objects((*scene)->ambient_light);
	free_scene_objects((*scene)->lights);
	free_scene_objects((*scene)->objects);
	free_bvh_tree((*scene)->tree);
	kill_free_threads(*scene);
	if ((*scene)->camera)
		free((*scene)->camera);
	if ((*scene)->win)
		mlx_destroy_window((*scene)->mlx, (*scene)->win);
	if ((*scene)->mlx)
		(mlx_destroy_display((*scene)->mlx), free((*scene)->mlx));
	free(*scene);
	*scene = NULL;
}

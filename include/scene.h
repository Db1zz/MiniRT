#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "object.h"
# include "ft_error.h"
# include "bvh.h"
# include "xpm_render.h"
# include "queue.h"

# include <pthread.h>
# include <semaphore.h>

# define SCENE_LIGHTS_LIMIT 10
# define SCENE_AMBIENT_LIGHTNING_LIMIT 10
# define SCENE_OBJECTS_LIMIT 1024
# define SCENE_ANTIALIASING_SAMPLES 10
# define SCENE_RENDER_DISTANCE 10.0f

typedef struct s_ray_thread_ctx t_ray_thread_ctx;

typedef struct s_scene
{
	void *win;
	void *mlx;
	t_camera *camera;
	t_object **lights;		  // [SCENE_LIGHTS_LIMIT + 1];
	t_object **ambient_light; // [SCENE_AMBIENT_LIGHTNING_LIMIT + 1];
	t_object **objects;		  // [SCENE_OBJECTS_LIMIT + 1];
	t_bvh_node *tree;
	t_xpm_image *img;
	size_t lights_size;
	size_t ambient_light_size;
	size_t objects_size;
	t_error error;
} t_scene;

t_error scene_add_object(t_scene *scene, t_object *object);
t_error scene_add_light(t_scene *scene, t_object *light);
t_error scene_add_ambient_light(t_scene *scene, t_object *ambient_light);
void	scene_update_tree(t_scene *scene);
t_error	scene_init(t_scene *scene);
void	scene_destroy(t_scene *scene);

#endif // SCENE_H
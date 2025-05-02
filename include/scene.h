#ifndef SCENE_H
# define SCENE_H

# include "camera.h"
# include "object.h"
# include "ft_error.h"
# include "bvh.h"
# include "xpm_render.h"
# include "queue.h"
# include "minirt_threads.h"

// typedef struct s_xpm_image t_xpm_image;

# include <pthread.h>
# include <semaphore.h>

# define SCENE_LIGHTS_LIMIT 10
# define SCENE_AMBIENT_LIGHTNING_LIMIT 10
# define SCENE_OBJECTS_LIMIT 1024
# define SCENE_ANTIALIASING_SAMPLES 10
# define SCENE_RENDER_DISTANCE 10.0f

typedef struct s_ray_thread_ctx t_ray_thread_ctx;
// typedef struct s_thread_sync t_thread_sync;

typedef struct s_scene
{
	void *win;
	void *mlx;
	t_camera *camera;
	t_object **lights;		  // [SCENE_LIGHTS_LIMIT + 1];
	t_object **ambient_light; // [SCENE_AMBIENT_LIGHTNING_LIMIT + 1];
	t_object **objects;		  // [SCENE_OBJECTS_LIMIT + 1];
	sem_t *thread_task_sem;
	sem_t *global_sem;
	t_ray_thread_ctx *threads_ctx;
	t_bvh_node *tree;
	t_xpm_image *img;
	t_thread_sync sync;
	size_t lights_size;
	size_t ambient_light_size;
	size_t objects_size;
	size_t threads_amount;
	t_error error;
} t_scene;

t_scene *scene_alloc(void);
void free_scene(t_scene **scene);

#endif // SCENE_H
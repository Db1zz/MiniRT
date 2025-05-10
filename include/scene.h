/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:55:19 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 13:55:19 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "camera.h" /* t_camera */
# include "object.h" /* t_object */
# include "ft_error.h" /* t_error */
# include "bvh.h" /* t_bvh_node */
# include "xpm_render.h" /* t_xpm_image */

# ifdef BONUS

#  define SCENE_LIGHTS_LIMIT 10
#  define SCENE_AMBIENT_LIGHTNING_LIMIT 10
#  define SCENE_OBJECTS_LIMIT 1024
#  define SCENE_RENDER_DISTANCE 1000.0f

# else

#  define SCENE_LIGHTS_LIMIT 1
#  define SCENE_AMBIENT_LIGHTNING_LIMIT 1
#  define SCENE_OBJECTS_LIMIT 1024
#  define SCENE_RENDER_DISTANCE 1000.0f

# endif // #ifdef BONUS

typedef struct s_scene
{
	void		*win;
	void		*mlx;
	t_camera	*camera;
	t_object	**lights; // [SCENE_LIGHTS_LIMIT + 1];
	t_object	**ambient_light; // [SCENE_AMBIENT_LIGHTNING_LIMIT + 1];
	t_object	**objects; // [SCENE_OBJECTS_LIMIT + 1];
	t_bvh_node	*tree;
	t_xpm_image	*img;
	size_t		lights_size;
	size_t		ambient_light_size;
	size_t		objects_size;
	t_error		error;
}	t_scene;

t_error	scene_add_object(t_scene *scene, t_object *object);
t_error	scene_add_light(t_scene *scene, t_object *light);
t_error	scene_add_ambient_light(t_scene *scene, t_object *ambient_light);
void	scene_update_tree(t_scene *scene);
t_error	scene_init(t_scene *scene);
void	scene_destroy(t_scene *scene);
t_color	scene_calculate_pixel_color(
			const t_camera *camera,
			const t_scene *scene,
			int x,
			int y);

#endif // SCENE_H
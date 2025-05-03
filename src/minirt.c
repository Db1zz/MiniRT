#include "ft_error.h"
#include "minirt.h"
#include "aabb.h"
#include "bvh.h"
#include "minirt_threads.h"

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int	exit_minirt(t_scene *scene)
{
	free_scene(&scene);
	exit(EXIT_SUCCESS);
}

int	input_handler(int key, t_scene *scene)
{
	usleep(10000);
	if (key == K_ESC)
		return (exit_minirt(scene));
	else if (key == K_D || key == K_S || key == K_A || key == K_W)
		return (move_camera_view_point(key, scene));
	else if (key == K_Z || key == K_X)
		return (move_camera_view_point(key, scene));
	else if (key == K_AR_L || key == K_AR_R || key == K_AR_U || key == K_AR_D)
		return (change_camera_orientation_vec(key, scene));
	return (0);
}

bool	minirt_init(t_scene *scene)
{
	if (!scene)
		return (false);
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx,
			VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "The rats have taken over");
	update_viewport(scene->camera);
	scene->img = xpm_render_new_img(
			scene->mlx,
			VIEWPORT_WIDTH,
			VIEWPORT_HEIGHT);
	mlx_hook(scene->win, 2, 1, input_handler, scene);
	mlx_hook(scene->win, 17, 1L << 17, exit_minirt, scene);
	return (true);
}

int minirt_routine(int argc, char **argv)
{
	t_scene		*scene;

	scene = parse_input(argc, argv);
	if (!minirt_init(scene))
	return (EXIT_FAILURE);

	scene->tree = create_tree(scene->objects, 0, scene->objects_size - 1, 0);
	print_tree(scene->tree);

	init_threads(scene);

	threads_render_image(scene);

	mlx_loop(scene->mlx);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}

// void lol() __attribute__((destructor))
// {
// 	printf("aboba\n");
// }

int main(int argc, char **argv)
{
	minirt_routine(argc, argv);
	return (EXIT_SUCCESS);
}

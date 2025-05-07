#include "minirt.h"

#include <stdlib.h> /* exit() */
#include <sys/mman.h> /* sysconf() */
#include <unistd.h> /* _SC_NPROCESSORS_CONF macro */

static int	exit_minirt(t_minirt_ctx *minirt)
{
	render_destroy_workers(&minirt->workers);
	scene_destroy(&minirt->scene);
	exit(EXIT_SUCCESS);
}

static int	minirt_movement_handler(int key, t_minirt_ctx *minirt)
{
	int ret;

	ret = key;
	if (key == K_D || key == K_S || key == K_A || key == K_W)
		ret = camera_move_view_point(key, minirt->scene.camera);
	else if (key == K_AR_L || key == K_AR_R || key == K_AR_U || key == K_AR_D)
		ret = camera_change_orientation_vector(key, minirt->scene.camera);
	render_scene(&minirt->scene, &minirt->workers);
	return (ret);
}

static int	minirt_input_handler(int key, t_minirt_ctx *minirt)
{
	if (key == K_ESC)
		return (exit_minirt(minirt));
	else if (key == K_D || key == K_S || key == K_A || key == K_W)
		return (minirt_movement_handler(key, minirt));
	else if (key == K_AR_L || key == K_AR_R || key == K_AR_U || key == K_AR_D)
		return (minirt_movement_handler(key, minirt));
	return (0);
}

bool	minirt_init(t_minirt_ctx *minirt, int argc, char **argv)
{
	size_t	num_workers;
	t_error	err;

	scene_init(&minirt->scene);
	err = parse_input(&minirt->scene, argc, argv);
	if (err.errorn)
		return (ft_display_error(&err), scene_destroy(&minirt->scene), false);
	minirt->scene.mlx = mlx_init();
	minirt->scene.win = mlx_new_window(
		minirt->scene.mlx,
		VIEWPORT_WIDTH,
		VIEWPORT_HEIGHT,
		"The rats have taken over");
		minirt->scene.img = xpm_render_new_img(
		minirt->scene.mlx,
		VIEWPORT_WIDTH,
		VIEWPORT_HEIGHT);
	update_viewport(minirt->scene.camera);
	num_workers = sysconf(_SC_NPROCESSORS_CONF);
	scene_update_tree(&minirt->scene);
	render_init_workers(&minirt->workers, num_workers, &minirt->scene);
	render_spawn_workers(&minirt->workers);
	mlx_hook(minirt->scene.win, 2, 1, minirt_input_handler, minirt);
	mlx_hook(minirt->scene.win, 17, 1L << 17, exit_minirt, minirt);
	return (true);
}


int	minirt_routine(int argc, char **argv)
{
	t_minirt_ctx minirt;

	if (!minirt_init(&minirt, argc, argv))
		return (EXIT_FAILURE);

	print_tree(minirt.scene.tree);
	render_scene(&minirt.scene, &minirt.workers);

	mlx_loop(minirt.scene.mlx);
	exit_minirt(&minirt);
	return (EXIT_SUCCESS);
}

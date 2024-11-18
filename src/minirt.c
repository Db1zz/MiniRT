#include "dependencies.h"
#include "minirt.h"

int	exit_minirt(t_scene *scene)
{
	free_scene(&scene);
	exit(0);
}

int	input_handler(int key, t_scene *scene)
{
	if (key == K_ESC)
		return (exit_minirt(scene));
}

int	main(int argc, char **argv)
{
	t_scene	*scene = parse_input(argc, argv);
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, 1024, 720, "I was crazy once");
	mlx_hook(scene->win, 2, 1, input_handler, scene);
	mlx_hook(scene->win, 17, 1L << 17, exit_minirt, scene);
	mlx_loop(scene->mlx);
	return (0);
}

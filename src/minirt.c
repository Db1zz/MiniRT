#include "dependencies.h"
#include "minirt.h"

int	exit_minirt(t_scene *scene)
{
	free_scene(&scene);
	exit(EXIT_SUCCESS);
}

int	input_handler(int key, t_scene *scene)
{
	if (key == K_ESC)
		return (exit_minirt(scene));
}

void	draw_line(t_scene *scene, int x, int y)
{
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			draw_pixel(scene, i, j, &(t_color){255, 0, 255});
		}
	}
}

int	main(int argc, char **argv)
{
	t_scene	*scene = parse_input(argc, argv);

	if (!scene)
		return (EXIT_FAILURE);
	scene->mlx = mlx_init();
	if (!scene->mlx)
	{
		printf("Mlx failed\n");
		return (EXIT_FAILURE);
	}
	scene->win = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT, "I was crazy once");
	if (!scene->win)
	{
		printf("Mlx failed\n");
		return (EXIT_FAILURE);
	}
	mlx_hook(scene->win, 2, 1, input_handler, scene);
	mlx_hook(scene->win, 17, 1L << 17, exit_minirt, scene);
	draw_line(scene, 100, 100);
	mlx_loop(scene->mlx);
	return (EXIT_SUCCESS);
}

#include "ft_error.h"
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
	return (0);
}

bool	minirt_init(t_scene *scene)
{
	if (!scene)
		return (false);
	scene->error = ERR_NO_ERROR;
	scene->antialiasing = true;
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(
			scene->mlx, WIN_WIDTH, WIN_HEIGHT, "The rats have taken over");
	update_viewport(scene->camera);
	mlx_hook(scene->win, 2, 1, input_handler, scene);
	mlx_hook(scene->win, 17, 1L << 17, exit_minirt, scene);
	return (true);
}

#include "timer.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	struct timeval start_time = getTime();

	scene = parse_input(argc, argv);
	if (!minirt_init(scene))
		return (EXIT_FAILURE);
	render(scene);

	struct timeval end_time = getTime();

	printf("Rendered for [m:%ld, s:%ld, ms:%ld]\n",
		getMinutesDiff(&start_time, &end_time),
		getSecondsDiff(&start_time, &end_time),
		getMilisecondsDiff(&start_time, &end_time));

	mlx_loop(scene->mlx);
	return (EXIT_SUCCESS);
}

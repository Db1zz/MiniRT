#include "ft_error.h"
#include "timer.h"
#include "minirt.h"
#include "aabb.h"

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
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(
			scene->mlx, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "The rats have taken over");
	update_viewport(scene->camera);
	mlx_hook(scene->win, 2, 1, input_handler, scene);
	mlx_hook(scene->win, 17, 1L << 17, exit_minirt, scene);
	return (true);
}

int	minirt_routine(int argc, char **argv) {
	t_scene	*scene;

	struct timeval	start_time = getTime();

	scene = parse_input(argc, argv);
	if (!minirt_init(scene))
		return (EXIT_FAILURE);

	struct timeval	end_time = getTime();

	printf("Rendered for [m:%ld, s:%ld, ms:%ld]\n",
		getMinutesDiff(&start_time, &end_time),
		getSecondsDiff(&start_time, &end_time),
		getMilisecondsDiff(&start_time, &end_time));

	mlx_loop(scene->mlx);
	return (EXIT_SUCCESS);
}

#include "timer.h"

int	main(int argc, char **argv)
{
	t_scene	*scene = parse_input(argc, argv);
	if (!scene)
		return (EXIT_FAILURE);

	minirt_init(scene);

	t_bvh_node	*tree = create_tree(scene->objects, 0, scene->objects_size);

	// t_aabb *box = scene->objects[1]->box;
	// printf("interval[0]: {%f, %f}\n", box->interval[0].min, box->interval[0].max);
	// printf("interval[1]: {%f, %f}\n", box->interval[1].min, box->interval[1].max);
	// printf("interval[2]: {%f, %f}\n", box->interval[2].min, box->interval[2].max);
	free_scene(&scene);

	return (EXIT_SUCCESS);
}

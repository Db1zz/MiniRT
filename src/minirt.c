#include "ft_error.h"
#include "timer.h"
#include "minirt.h"
#include "aabb.h"
#include "bvh.h"

#include <assert.h>

int exit_minirt(t_scene *scene)
{
	free_scene(&scene);
	exit(EXIT_SUCCESS);
}

int input_handler(int key, t_scene *scene)
{
	if (key == K_ESC)
		return (exit_minirt(scene));
	return (0);
}

bool minirt_init(t_scene *scene)
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

int minirt_routine(int argc, char **argv)
{
	t_scene *scene;
	t_bvh_node *tree;

	scene = parse_input(argc, argv);
	if (!minirt_init(scene))
		return (EXIT_FAILURE);

	tree = create_tree(scene->objects, 0, scene->objects_size - 1, 0);
	print_tree(tree);

	struct timeval start_time = getTime();
	render(scene, tree);
	struct timeval end_time = getTime();

	printf("Rendered for [m:%ld, s:%ld, ms:%ld]\n",
		   getMinutesDiff(&start_time, &end_time),
		   getSecondsDiff(&start_time, &end_time),
		   getMilisecondsDiff(&start_time, &end_time));

	mlx_loop(scene->mlx);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}

#include "timer.h"

void display_interval(const t_interval *interval)
{
	printf("[%f, %f]", interval->min, interval->max);
}

void test_merge_sort(t_scene *scene)
{
	merge_sort_objects_array(scene->objects, 0, scene->objects_size - 1, box_x_compare_is_less);

	for (int i = 0; i < scene->objects_size; ++i)
	{
		// t_sphere *sphere = scene->objects[i]->data;
		// printf("pos[%f, %f, %f]\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
		display_interval(&scene->objects[i]->box->interval[0]);
		display_interval(&scene->objects[i]->box->interval[1]);
		display_interval(&scene->objects[i]->box->interval[2]);
		printf("\n\n");
	}
}

int main(int argc, char **argv)
{
	// t_scene *scene = parse_input(argc, argv);
	// if (!scene)
	// 	return (EXIT_FAILURE);

	// minirt_init(scene);
	minirt_routine(argc, argv);

	// test_merge_sort(scene);

	// t_bvh_node *tree = create_tree(scene->objects, 0, scene->objects_size - 1);
	// print_tree(tree);

	// t_aabb *box = scene->objects[1]->box;
	// printf("interval[0]: {%f, %f}\n", box->interval[0].min, box->interval[0].max);
	// printf("interval[1]: {%f, %f}\n", box->interval[1].min, box->interval[1].max);
	// printf("interval[2]: {%f, %f}\n", box->interval[2].min, box->interval[2].max);
	// free_scene(&scene);

	return (EXIT_SUCCESS);
}

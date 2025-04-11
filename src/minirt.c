#include "ft_error.h"
#include "timer.h"
#include "minirt.h"
#include "aabb.h"

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

	struct timeval start_time = getTime();

	scene = parse_input(argc, argv);
	if (!minirt_init(scene))
		return (EXIT_FAILURE);

	struct timeval end_time = getTime();

	printf("Rendered for [m:%ld, s:%ld, ms:%ld]\n",
		   getMinutesDiff(&start_time, &end_time),
		   getSecondsDiff(&start_time, &end_time),
		   getMilisecondsDiff(&start_time, &end_time));

	mlx_loop(scene->mlx);
	return (EXIT_SUCCESS);
}

#include "timer.h"

void display_interval(const t_interval *interval)
{
	printf("[%f, %f]", interval->min, interval->max);
}

void test_merge_sort(t_scene *scene)
{
	merge_sort_list(scene->objects, 0, scene->objects_size - 1, box_x_compare_is_less);

	for (int i = 0; i < scene->objects_size; ++i)
	{
		t_sphere *sphere = scene->objects[i]->data;
		// printf("pos[%f, %f, %f]\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
		display_interval(&scene->objects[i]->box->interval[0]);
		display_interval(&scene->objects[i]->box->interval[1]);
		display_interval(&scene->objects[i]->box->interval[2]);
		printf("\n\n");
	}
}

void print_tree_routine(
	t_bvh_node *tree, int level, char *buffer, size_t buffer_size);

void print_tree(t_bvh_node *tree)
{
	size_t buffer_size = 1024;
	char buffer[buffer_size + 1];
	buffer[0] = '\0';
	printf("N\n");
	print_tree_routine(tree, 0, buffer, buffer_size);
}

void print_spaces(int x)
{
	int i = 0;

	while (i++ < x)
		printf(" ");
}

void print_tree_line(
	char *node_str, int level, char *buffer, size_t buffer_size)
{
	int i;
	int printed;
	int spaces_consumed;

	i = 0;
	printed = 0;
	spaces_consumed = 0;
	while (buffer[i] && i < level)
	{
		printed += printf("%c", buffer[i++]);
		spaces_consumed += printf(" ");
	}
	print_spaces(level - spaces_consumed + (level - printed));
	printf("%s\n", node_str);
}

#include <assert.h> // only for print_tree_routine

void print_tree_routine(
	t_bvh_node *tree, int level, char *buffer, size_t buffer_size)
{
	if (tree == NULL)
		return;
	/*
	   buffer_size = 1024
	   [N,|-N,| └─N,|  └─N]
		N
		|-N
		| └─N
		|   └─ N
		|      |-N
		|      | |- N
		|	   | └─ N
		|      └─N
		└─N
		level == (depth level && buffer index)
	*/
	if (tree->left && tree->right)
	{
		print_tree_line("|-N", level, buffer, buffer_size);
		buffer[level] = '|';
		print_tree_routine(tree->left, level + 1, buffer, buffer_size);
	}
	buffer[level + 1] = '\0';
	if (tree->objects)
	{
		assert(tree->objects && !tree->left && !tree->right); // REMOVEME
		print_tree_line("└─Sphere", level, buffer, buffer_size);
	}
	else
	{
		print_tree_line("└─N", level, buffer, buffer_size);
		if (tree->right)
			print_tree_routine(tree->right, level + 1, buffer, buffer_size);
		else
			print_tree_routine(tree->left, level + 1, buffer, buffer_size);
	}
	if (level - 1 >= 0)
		buffer[level - 1] = '\0';
}

int main(int argc, char **argv)
{
	t_scene *scene = parse_input(argc, argv);
	if (!scene)
		return (EXIT_FAILURE);

	minirt_init(scene);

	// test_merge_sort(scene);

	t_bvh_node *tree = create_tree(scene->objects, 0, scene->objects_size - 1);
	print_tree(tree);

	// t_aabb *box = scene->objects[1]->box;
	// printf("interval[0]: {%f, %f}\n", box->interval[0].min, box->interval[0].max);
	// printf("interval[1]: {%f, %f}\n", box->interval[1].min, box->interval[1].max);
	// printf("interval[2]: {%f, %f}\n", box->interval[2].min, box->interval[2].max);
	free_scene(&scene);

	return (EXIT_SUCCESS);
}

#include "ft_error.h"
#include "timer.h"
#include "minirt.h"
#include "aabb.h"
#include "bvh.h"
#include "minirt_threads.h"

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int exit_minirt(t_scene *scene)
{
	free_scene(&scene);
	exit(EXIT_SUCCESS);
}

int input_handler(int key, t_scene *scene)
{
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

bool minirt_init(t_scene *scene)
{
	if (!scene)
		return (false);
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(
		scene->mlx, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "The rats have taken over");
	update_viewport(scene->camera);

	scene->img = xpm_render_new_img(
		scene->mlx,
		VIEWPORT_WIDTH,
		VIEWPORT_HEIGHT);

	mlx_hook(scene->win, 2, 1, input_handler, scene);
	mlx_hook(scene->win, 17, 1L << 17, exit_minirt, scene);
	return (true);
}

int **alloc_matrix(size_t matrix_size) {
	int		**matrix;
	size_t	rows = matrix_size;
	size_t	columns = VIEWPORT_WIDTH * VIEWPORT_HEIGHT / rows;

	matrix = ft_calloc(rows, sizeof(int *));
	for (size_t i = 0; i < matrix_size; ++i) {
		matrix[i] = ft_calloc(columns, sizeof(int));
	}
	return (matrix);
}

void init_threads(t_scene *scene) {
	size_t				i;
	t_ray_thread_ctx	*thread_data;

	i = 0;
	scene->threads_amount = sysconf(_SC_NPROCESSORS_CONF);
	scene->threads = ft_calloc(scene->threads_amount, sizeof(pthread_t));
	init_semaphore(&scene->thread_task_sem, "minirt_thread_task_sem", scene->threads_amount);
	init_semaphore(&scene->global_sem, "minirt_global_sem", 1);
	scene->tasks_fineshed = 0;

	while (i < scene->threads_amount)
	{
		thread_data = ft_calloc(1, sizeof(t_ray_thread_ctx));
		thread_data->start_x = VIEWPORT_HEIGHT / scene->threads_amount * i;
		thread_data->end_x = thread_data->start_x + VIEWPORT_HEIGHT / scene->threads_amount;
		if (i == scene->threads_amount - 1)
			thread_data->end_x += VIEWPORT_HEIGHT % scene->threads_amount;
		thread_data->scene = scene;
		thread_data->tid = i;
		pthread_create(&scene->threads[i], NULL, ray_task_handler, thread_data);
		++i;
	}
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

	struct timeval start_time = getTime();
	render(scene);
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

// void lol() __attribute__((destructor))
// {
// 	printf("aboba\n");
// }

int main(int argc, char **argv)
{
	minirt_routine(argc, argv);
	return (EXIT_SUCCESS);
}

#include "minirt_threads.h"
#include "scene.h" /* scene */
#include "libft.h" /* ft_calloc */

#include <unistd.h> /* _SC_NPROCESSORS_CONF macro */
#include <sys/types.h> /* sysconf */

bool	thread_init(t_scene *scene)
{
	t_ray_thread_ctx	*threads_ctx;
	size_t				i;
	size_t				perv_end;

	i = 0;
	scene->threads_amount = sysconf(_SC_NPROCESSORS_CONF);
	scene->threads_ctx = ft_calloc(scene->threads_amount, sizeof(t_ray_thread_ctx));
	pepe_barrier_init(&(scene->start_render_barrier), NULL, scene->threads_amount + 1);
	pepe_barrier_init(&(scene->end_render_barrier), NULL, scene->threads_amount + 1);
	threads_ctx = scene->threads_ctx;
	perv_end = 0;
	while (i < scene->threads_amount)
	{
		threads_ctx[i].start_x = perv_end;
		threads_ctx[i].end_x = perv_end + (VIEWPORT_HEIGHT / scene->threads_amount + ((VIEWPORT_HEIGHT - perv_end) % (scene->threads_amount - i)));
		threads_ctx[i].scene = scene;
		threads_ctx[i].tid = i;
		perv_end = threads_ctx[i].end_x;
		pthread_create(&scene->threads_ctx[i].pt, NULL, thread_render_routine, &threads_ctx[i]);
		++i;
	}
	return (true);
}

static void	thread_stop_multiple(t_ray_thread_ctx *ctx)
{

}

void	thread_destroy()
{

}
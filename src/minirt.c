/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:01:47 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 01:01:47 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "parser.h"
#include "mlx.h"

#include <stdlib.h>	  /* exit() */

static int	exit_minirt(t_minirt_ctx *minirt)
{
	scene_destroy(&minirt->scene);
	exit(EXIT_SUCCESS);
}

static int	minirt_input_handler(int key, t_minirt_ctx *minirt)
{
	if (key == K_ESC)
		return (exit_minirt(minirt));
	return (0);
}

static bool	minirt_init(t_minirt_ctx *minirt, int argc, char **argv)
{
	t_error	err;

	scene_init(&minirt->scene);
	err = parse_input(&minirt->scene, argc, argv);
	if (err.errorn)
		return (ft_display_error(&err), scene_destroy(&minirt->scene), false);
	camera_update_viewport(minirt->scene.camera);
	scene_update_tree(&minirt->scene);
	mlx_hook(minirt->scene.win, 2, 1, minirt_input_handler, minirt);
	mlx_hook(minirt->scene.win, 17, 1L << 17, exit_minirt, minirt);
	return (true);
}

int	minirt_routine(int argc, char **argv)
{
	t_minirt_ctx	minirt;

	if (!minirt_init(&minirt, argc, argv))
		return (EXIT_FAILURE);
	print_tree(minirt.scene.tree);
	render_scene(&minirt.scene);
	mlx_loop(minirt.scene.mlx);
	exit_minirt(&minirt);
	return (EXIT_SUCCESS);
}

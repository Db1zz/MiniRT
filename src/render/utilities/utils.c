/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:52 by gonische          #+#    #+#             */
/*   Updated: 2025/02/11 18:28:52 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	*rt_calloc(
	size_t count,
	size_t size,
	t_scene *scene)
{
	void	*result;

	result = malloc(count * size);
	if (!result)
		return (set_error(scene->error, ERR_MALLOC_FAILED), NULL);
	ft_bzero(result, count * size);
	return (result);
}

void	free_2dmatrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

size_t	get_2dmatrix_size(char **matrix)
{
	size_t	size;

	if (matrix == NULL)
		return (0);
	size = 0;
	while (matrix[size])
		size++;
	return (size);
}

void	free_scene(t_scene **scene)
{
	if (!scene || !*scene)
		return ;
	free_object_list(&(*scene)->objects);
	if ((*scene)->camera)
		free((*scene)->camera);
	if ((*scene)->win)
		mlx_destroy_window((*scene)->mlx, (*scene)->win);
	if ((*scene)->mlx)
	{
		#ifndef __APPLE__	// Temp macro
			mlx_destroy_display((*scene)->mlx);
		#endif	// __APPLE__
		free((*scene)->mlx);
	}
	free(*scene);
	*scene = NULL;
}

double	div_c(double v1, double v2)
{
	if (v2 == 0)
		return (0);
	return (v1 / v2);
}

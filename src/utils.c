/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:42:46 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 17:37:54 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_2dmatrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

bool	is_string_number(char *line)
{
	int	i;

	if (line == NULL)
	{
		printf("Error in %s: line == NULL", __func__);
		return (false);
	}
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
			return (false);
		i++;
	}
	return (true);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:26:18 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 21:15:27 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include "minirt.h"

int	set_vector(t_vector *vector, float x, float y, float z)
{
	if (!vector)
	{
		printf("Error in %s: vector == NULL\n", __func__);
		return (-1);
	}
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (0);
}

int		str_to_vector(t_vector *vector, const char *vector_str)
{
	char	**data;
	int		status;

	if (!vector || !vector_str)
	{
		printf("Error in %s: vector | vector_str == NULL\n", __func__);
		return (-1);
	}
	status = 0;
	data = ft_split(vector_str, ',');
	if (!check_str_numbers(data, VECTOR_MAX_SIZE))
	{
		printf("Error in %s: Cannot convert non-numeric string to vector.\n",
				__func__);
		status = -1;
	}
	if (!status && set_vector(vector, ft_atof(data[0]),
				ft_atof(data[1]), ft_atof(data[2])))
		status = -1;
	free_2dmatrix(data);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:03 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 14:35:55 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	normalize_vector(t_pos *vector)
{
	double	magnitude;

	if (!vector)
	{
		printf("Error in %s: vector == NULL\n", __func__);
		return (-1);
	}
	magnitude = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	vector->x = vector->x / magnitude;
	vector->y = vector->y / magnitude;
	vector->z = vector->z / magnitude;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:26:18 by gonische          #+#    #+#             */
/*   Updated: 2024/11/09 12:49:32 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pos.h"
#include "minirt.h"

void	init_pos(t_pos *pos, char *pos_str)
{
	char	**positions;

	positions = ft_split(pos_str, ',');
	pos->x = ft_atof(positions[0]);
	pos->y = ft_atof(positions[1]);
	pos->z = ft_atof(positions[2]);
	free_2dmatrix(positions);
}

void	set_pos(t_pos *pos, float x, float y, float z)
{
	if (!pos)
	{
		printf("Error in %s: pos == NULL\n", __func__);
		return ;
	}
	pos->x = x;
	pos->y = y;
	pos->z = z;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:26:18 by gonische          #+#    #+#             */
/*   Updated: 2024/11/07 12:29:40 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pos.h"

void	set_pos(t_pos *pos, int x, int y, int z)
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

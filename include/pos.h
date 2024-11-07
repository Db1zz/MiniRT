/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:26:26 by gonische          #+#    #+#             */
/*   Updated: 2024/11/07 12:28:45 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POS_H
# define POS_H

typedef struct s_pos
{
	int	x;
	int	y;
	int	z;
}	t_pos;

void	set_pos(t_pos *pos, int x, int y, int z);

#endif // POS_H
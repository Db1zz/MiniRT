/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:26:26 by gonische          #+#    #+#             */
/*   Updated: 2024/11/08 18:05:20 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POS_H
# define POS_H

typedef struct s_pos
{
	float	x;
	float	y;
	float	z;
}	t_pos;

void	init_pos(t_pos *pos, char *pos_str);
void	set_pos(t_pos *pos, float x, float y, float z);

#endif // POS_H
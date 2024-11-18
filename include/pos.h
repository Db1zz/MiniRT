/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:26:26 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 18:06:35 by gwagner          ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:45:43 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:45:43 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "vector.h"

# define VIEWPORT_WIDTH 1920
# define VIEWPORT_HEIGHT 1024

typedef struct s_viewport
{
	t_vector	first_pixel;
	t_vector	pdelta_x;
	t_vector	pdelta_y;
	t_vector	upper_left;
	t_vector	horizontal_vec;
	t_vector	verical_vec;
	double		height;
	double		width;

}	t_viewport;

void	update_viewport(t_viewport *vp, double fov, t_vector view_point);

#endif // VIEWPORT_H
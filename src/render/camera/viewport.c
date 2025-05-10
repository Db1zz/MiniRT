/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:27:34 by gonische          #+#    #+#             */
/*   Updated: 2025/04/07 18:28:34 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

#include "minirt_math.h" /* FT_PI */
#include "vector.h" /* t_vector | functions */

#include <math.h> /* tan() */

static double	fov_to_height(double fov)
{
	return (tan((FT_PI * 0.5 * fov) / 180));
}

void	update_viewport(t_viewport *vp, double fov, t_vector view_point)
{
	vp->height = fov_to_height(fov);
	vp->width = ((double)VIEWPORT_WIDTH / VIEWPORT_HEIGHT) * vp->height;
	vp->horizontal_vec = create_vector(vp->width, 0, 0);
	vp->verical_vec = create_vector(0, -vp->height, 0);
	vp->upper_left = vec3_sub_vec3(
			vec3_sub_vec3(
				vec3_sub_vec3(view_point, create_vector(0, 0, 1)),
				vec3_div(vp->horizontal_vec, 2.0)),
			vec3_div(vp->verical_vec, 2.0));
	vp->pdelta_x = vec3_div(vp->horizontal_vec, VIEWPORT_WIDTH);
	vp->pdelta_y = vec3_div(vp->verical_vec, VIEWPORT_HEIGHT);
	vp->first_pixel = vec3_add_vec3(vp->upper_left,
			vec3_mult(vec3_add_vec3(vp->pdelta_x, vp->pdelta_y), 0.5));
}

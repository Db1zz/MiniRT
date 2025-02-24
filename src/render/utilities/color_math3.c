/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:24:12 by gonische          #+#    #+#             */
/*   Updated: 2025/02/11 18:24:12 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "minirt_math.h"

t_color	clamp_color(t_color color, double min, double max)
{
	return (create_color(clamp_value(color.r, min, max),
			clamp_value(color.g, min, max),
			clamp_value(color.b, min, max)));
}

t_color	filter_color(t_color clr1, t_color clr2)
{
	return (clr_mult(clr_div_clr(clr1, clr2), COLOR_MAX));
}

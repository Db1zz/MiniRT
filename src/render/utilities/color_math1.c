/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:24:28 by gonische          #+#    #+#             */
/*   Updated: 2025/05/06 11:31:04 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "minirt.h"
#include "utils.h"

t_color	clr_div_clr(t_color c1, t_color c2)
{
	return ((t_color){
		div_c(c1.r, c2.r),
		div_c(c1.g, c2.g),
		div_c(c1.b, c2.b)});
}

t_color	clr_mult_clr(t_color c1, t_color c2)
{
	return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

t_color	clr_sub_clr(t_color c1, t_color c2)
{
	return ((t_color){c1.r - c2.r, c1.g - c2.g, c1.b - c2.b});
}

t_color	clr_add_clr(t_color c1, t_color c2)
{
	return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

t_color	int_to_rgb(int x)
{
	return ((t_color){(x >> 16) & 0xFF,
		(x >> 8) & 0xFF, x & 0xFF});
}
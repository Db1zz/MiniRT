/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:21:34 by gonische          #+#    #+#             */
/*   Updated: 2024/11/07 12:23:19 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

bool	set_color(t_color *color, int r, int g, int b)
{
	if (!color)
	{
		printf("Error in %s: color == NULL\n", __func__);
		return (false);
	}
	if (!validate_colors(r, g, b))
		return (false);
	color->r = r;
	color->g = g;
	color->b = b;
	return (true);
}

bool	check_color(int c)
{
	return (c >= RGB_MIN && c <= RGB_MAX);
}

bool	validate_colors(int r, int g, int b)
{
	return (check_color(r) && check_color(g) && check_color(b));
}

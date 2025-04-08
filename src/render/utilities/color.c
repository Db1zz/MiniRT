/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:26:07 by gonische          #+#    #+#             */
/*   Updated: 2025/04/07 19:15:38 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"
#include "minirt.h"

t_color	create_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}

t_errorn	set_color(t_color *color, double r, double g, double b)
{
	if (!color)
		return (ERR_NULL_PARAMETER);
	if (!validate_colors(r, g, b))
		return (ERR_INCORRECT_COLOR_VALUES);
	color->r = r;
	color->g = g;
	color->b = b;
	return (ERR_NO_ERROR);
}

bool	check_color(double c)
{
	return (c >= COLOR_MIN && c <= COLOR_MAX);
}

bool	validate_colors(double r, double g, double b)
{
	return (check_color(r) && check_color(g) && check_color(b));
}

int	rgb_to_int(t_color color)
{
	return (65536 * (int)color.r + 256 * (int)color.g + (int)color.b);
}

void	print_color(t_color *c)
{
	printf("Color: [%f, %f, %f]\n", c->r, c->g, c->b);
}

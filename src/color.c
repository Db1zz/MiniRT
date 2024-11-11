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
#include "libft.h"

int	set_color(t_color *color, int r, int g, int b)
{
	if (!color)
	{
		printf("Error in %s: color == NULL\n", __func__);
		return (-1);
	}
	if (!validate_colors(r, g, b))
		return (-1);
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}

bool	check_color(int c)
{
	return (c >= RGB_MIN && c <= RGB_MAX);
}

bool	validate_colors(int r, int g, int b)
{
	return (check_color(r) && check_color(g) && check_color(b));
}

int		str_to_color(t_color *color, char *str)
{
	char	**data;

	if (!color || !str)
	{
		printf("Error in %s: color | str == NULL\n", __func__);
		return (-1);
	}
	data = ft_split(str, ',');
	if (data == NULL || get_2dmatrix_size(data) != RGB_MAX_SIZE)
	{
		printf("Error in %s: color size != %d\n", __func__, RGB_MAX_SIZE);
		return (-1);
	}
	// what if input will be "0,,"
	return (0);
}

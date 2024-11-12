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
#include "minirt.h"

int	set_color(t_color *color, int r, int g, int b)
{
	if (!color)
	{
		printf("Error in %s: color == NULL\n", __func__);
		return (-1);
	}
	if (!validate_colors(r, g, b))
	{
		printf("Error in %s: Incorrect color values\n", __func__);
		return (-1);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}

bool	check_color(int c)
{
	return (c >= COLOR_MIN && c <= COLOR_MAX);
}

bool	validate_colors(int r, int g, int b)
{
	return (check_color(r) && check_color(g) && check_color(b));
}

int		str_to_color(t_color *color, const char *str)
{
	char	**data;
	int		status;

	status = 0;
	if (!color || !str)
	{
		printf("Error in %s: color | str == NULL\n", __func__);
		return (-1);
	}
	data = ft_split(str, ',');
	if (check_str_numbers(data, COLOR_MAX_SIZE))
	{
		printf("Error in %s: Cannot convert non-numeric string to color.\n",
				__func__);
		status = -1;
	}
	if (!status && set_color(color, ft_atoi(data[0]),
				ft_atoi(data[1]), ft_atoi(data[2])))
		status = -1;
	free_2dmatrix(data);
	return (status);
}

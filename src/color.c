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
	bool	status;
	int		i;

	status = false;
	while (true)
	{
		// TODO fix this
		if (!color || !str)
			printf("Error in %s: color | str == NULL\n", __func__);
		data = ft_split(str, ',');
		if (data == NULL || get_2dmatrix_size(data) != RGB_MAX_SIZE)
			printf("Error in %s: color size != %d\n", __func__, RGB_MAX_SIZE);
		i = 0;
		while (i < RGB_MAX_SIZE)
		{
			if (!is_string_number(str))
			{
				printf("Error in %s: string is not a number\n", __func__);
				break ;
			}
			i++;
		}
		status = set_color(color, ft_atoi(data[0]), ft_atoi(data[1]), ft_atoi(data[2]));
		break ;
	}
	free_2dmatrix(data);
	if (!status)
		return (-1);
	return (0);
}

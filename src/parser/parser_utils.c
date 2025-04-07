/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:29:33 by gonische          #+#    #+#             */
/*   Updated: 2025/04/03 22:18:57 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "ft_error.h"
#include "ray.h"
#include "vector.h"
#include "utils.h"

bool	check_str_numbers(char **numbers, int expected_size, t_scene *scene)
{
	int	i;

	i = 0;
	while (numbers[i] != NULL)
	{
		if (i > expected_size || !is_string_number(numbers[i], scene))
			return (false);
		i++;
	}
	if (i == expected_size)
		return (true);
	return (false);
}

void	str_to_color(t_color *color, const char *str, t_scene *scene)
{
	char	**data;

	if (!color || !str)
		return (set_error(&scene->error, ERR_NULL_PARAMETER, __func__));
	data = ft_split(str, ',');
	if (!data)
		return (set_error(&scene->error, ERR_SPLIT_FAILED, __func__));
	if (!check_str_numbers(data, COLOR_MAX_SIZE, scene))
		return (set_error(&scene->error, ERR_STR_TO_COLOR_FAILED, __func__));
	set_color(color, ft_atoi(data[0]), ft_atoi(data[1]), ft_atoi(data[2]));
	free_2dmatrix(data);
}

void	str_to_vector(
	t_vector *result,
	const char *vector_str,
	bool normalize,
	t_scene *scene)
{
	char	**data;

	if (!result || !vector_str)
		return (set_error(&scene->error, ERR_NULL_PARAMETER, __func__));
	*result = create_vector(0, 0, 0);
	data = ft_split(vector_str, ',');
	if (!data)
		return (set_error(&scene->error, ERR_SPLIT_FAILED, __func__));
	if (!check_str_numbers(data, VECTOR_MAX_SIZE, scene))
		return (set_error(&scene->error, ERR_STR_TO_VECTOR_FAILED, __func__));
	set_vector(result, ft_atof(data[0]), ft_atof(data[1]), ft_atof(data[2]));
	free_2dmatrix(data);
	if (normalize)
		*result = vec3_normalize(*result);
}

bool	is_string_number(const char *number, t_scene *scene)
{
	int	i;

	i = 0;
	if (!number
		|| (!ft_isdigit(number[i]) && number[i] != '-' && number[i] != '+'))
		return (set_error(&scene->error, ERR_NULL_PARAMETER, __func__), false);
	if (number[i] == '-')
		i += 2;
	else
		i++;
	if (number[i] == '.')
		i++;
	while (number[i])
	{
		if (!ft_isdigit(number[i]) && number[i] != '\n')
			return (set_error(&scene->error, ERR_STRING_IS_NOT_NUM, __func__), false);
		i++;
	}
	return (true);
}

double	rt_atof(const char *str, t_scene *scene)
{
	double	result;
	double	point_val;
	int		i;
	int		neg;

	if (!is_string_number(str, scene))
		return (0);
	neg = 1;
	i = 0;
	result = ft_atoi(str);
	point_val = 0;
	if (result < 0 || str[0] == '-')
		neg = -1;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i])
		return (result);
	point_val += ft_atoi(str + i + 1);
	if (point_val < 0 || (point_val == 0 && !ft_isdigit(str[i + 1])))
		return (0);
	if (!ft_isdigit(str[i + 1]))
		return (result);
	while (0 < (int)point_val)
		point_val /= 10;
	return (result + point_val * neg);
}

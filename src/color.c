#include "color.h"
#include "libft.h"
#include "minirt.h"

t_error	set_color(t_color *color, int r, int g, int b)
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

bool	check_color(int c)
{
	return (c >= COLOR_MIN && c <= COLOR_MAX);
}

bool	validate_colors(int r, int g, int b)
{
	return (check_color(r) && check_color(g) && check_color(b));
}

t_error	str_to_color(t_color *color, const char *str)
{
	t_error	errorn;
	char	**data;

	if (!color || !str)
		return (ERR_NULL_PARAMETER);
	errorn = ERR_NO_ERROR;
	data = ft_split(str, ',');
	if (!data)
		return (ERR_SPLIT_FAILED);
	if (check_str_numbers(data, COLOR_MAX_SIZE))
		errorn = ERR_STR_TO_COLOR_FAILED;
	if (!errorn)
		errorn = set_color(color, ft_atoi(data[0]), ft_atoi(data[1]), ft_atoi(data[2]));
	free_2dmatrix(data);
	return (errorn);
}

#include "color.h"
#include "libft.h"
#include "minirt.h"
#include "libc.h"

t_color	create_color(int r, int g, int b)
{
	return ((t_color){r, g, b});
}

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

int	rgb_to_int(t_color color)
{
	return (65536 * color.r + 256 * color.g + color.b);
}

void	print_color(t_color *c)
{
	printf("Color: [%d, %d, %d]\n", c->r, c->g, c->b);
}

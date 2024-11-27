#include "color.h"

t_color	color_div(t_color color, double val)
{
	return ((t_color){color.r / val, color.g / val, color.b / val});
}

t_color	color_mult(t_color color, double val)
{
	return ((t_color){color.r * val, color.g * val, color.b * val});
}

t_color	color_sub(t_color color, int val)
{
	return ((t_color){color.r - val, color.g - val, color.b - val});
}

t_color	color_add(t_color color, int val)
{
	return ((t_color){color.r + val, color.g + val, color.b + val});
}

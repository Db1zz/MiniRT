#include "color.h"
#include "minirt_math.h"
#include "minirt.h"

t_color	clr_div(t_color color, double val)
{
	return ((t_color){color.r / val, color.g / val, color.b / val});
}

t_color	clr_mult(t_color color, double val)
{
	return ((t_color){color.r * val, color.g * val, color.b * val});
}

t_color	clr_sub(t_color color, int val)
{
	return ((t_color){color.r - val, color.g - val, color.b - val});
}

t_color	clr_add(t_color color, int val)
{
	return ((t_color){color.r + val, color.g + val, color.b + val});
}

t_color	normalize_color(t_color color)
{
	color.r = clamp_value(color.r, COLOR_MIN, COLOR_MAX);
	color.g = clamp_value(color.g, COLOR_MIN, COLOR_MAX);
	color.b = clamp_value(color.b, COLOR_MIN, COLOR_MAX);
	return (color);
}

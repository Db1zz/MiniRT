#include "color.h"

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

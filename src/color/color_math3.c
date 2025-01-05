#include "color.h"
#include "minirt_math.h"

t_color	clamp_color(t_color color, int min, int max)
{
	return (create_color(clamp_value(color.r, min, max),
						clamp_value(color.g, min, max),
						clamp_value(color.b, min, max)));
}

t_color	filter_color(t_color clr1, t_color clr2)
{
	return (clr_mult(clr_div_clr(clr1, clr2), COLOR_MAX));
}

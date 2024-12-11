#include "color.h"	

double	div_a(double v1, double v2)
{
	if (v2 == 0)
		return (0);
	return (v1 / v2);
}

/*
	div_a == cringe
*/
t_color	clr_div_clr(t_color c1, t_color c2)
{
	return (color(div_a(c1.r, c2.r), div_a(c1.g, c2.g), div_a(c1.b, c2.b)));
}

t_color	clr_mult_clr(t_color c1, t_color c2)
{
	return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

t_color	clr_sub_clr(t_color c1, t_color c2)
{
	return ((t_color){c1.r - c2.r, c1.g - c2.g, c1.b - c2.b});
}

t_color	clr_add_clr(t_color c1, t_color c2)
{
	return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

#ifndef COLOR_H
# define COLOR_H

# define COLOR_MIN 0
# define COLOR_MAX 255
# define COLOR_MAX_SIZE 3
# define WHITE 255, 255, 255

# include "ft_error.h"
# include <stdbool.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

t_error	set_color(t_color *color, int r, int g, int b);
bool	check_color(int c);
int		rgb_to_int(t_color color);
bool	validate_colors(int r, int g, int b);
t_error	str_to_color(t_color *color, const char *str);
void	print_color(t_color *c);
t_color	color(int r, int g, int b);

t_color	clr_div_clr(t_color c1, t_color c2);
t_color	clr_mult_clr(t_color c1, t_color c2);
t_color	clr_sub_clr(t_color c1, t_color c2);
t_color	clr_add_clr(t_color c1, t_color c2);

t_color	clr_div(t_color color, double val);
t_color	clr_mult(t_color color, double val);
t_color	clr_sub(t_color color, int val);
t_color	clr_add(t_color color, int val);
t_color	normalize_color(t_color color);
t_color	clamp_color(t_color color, int min, int max);
t_color	filter_color(t_color clr1, t_color clr2);

#endif // COLOR_H
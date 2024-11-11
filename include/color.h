/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:20:14 by gonische          #+#    #+#             */
/*   Updated: 2024/11/07 12:29:57 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define RGB_MIN 0
# define RGB_MAX 255
# define RGB_MAX_SIZE 3

# include <stdbool.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

int		set_color(t_color *color, int r, int g, int b);
bool	check_color(int c);
bool	validate_colors(int r, int g, int b);
int		str_to_color(t_color *color, char *str);


#endif // COLOR_H
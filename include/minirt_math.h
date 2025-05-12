/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:35:34 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 15:56:07 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# ifndef FT_EPSILON
#  define FT_EPSILON 1e-4
# endif // FT_EPSILON

# include <math.h> /* INFINITY */
# include <stdbool.h>

/* Useful math constants */
# define FT_PI		3.14159265358979323846
# define FT_INFINITY	INFINITY

/* Functions */
double	degrees_to_radians(double degrees);
double	random_double(void);
double	random_double_range(double min, double max);
double	clamp_value(double val, double min, double max);
bool	quadratic(double a, double b, double c, double *result);
int		rand_int(int min, int max);
void	set_double(double *var, double val);

#endif // MINIRT_MATH_H
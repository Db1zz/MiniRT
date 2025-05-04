/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:32 by gonische          #+#    #+#             */
/*   Updated: 2025/04/28 13:38:10 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"
#include "color.h"
#include "libft.h"
#include <stdlib.h>
#include <assert.h>

double	degrees_to_radians(double degrees)
{
	return ((FT_PI / 180) * degrees);
}

double	random_double(void)
{
	return (rand() / ((double)RAND_MAX + 1.0f));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	clamp_value(double val, double min, double max)
{
	if (val > max)
		return (max);
	else if (val < min)
		return (min);
	return (val);
}

bool	quadratic(double a, double b, double c, double *result)
{
	double	discriminant;
	double	sqrt_discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	sqrt_discriminant = sqrt(discriminant);
	result[0] = (-b + sqrt_discriminant) / (2 * a);
	result[1] = (-b - sqrt_discriminant) / (2 * a);
	return (true);
}

int rand_int(int min, int max) {
	int	randomized_value;

	randomized_value = random_double_range(min, max + 1);
	assert(randomized_value >= min && randomized_value <= max);

	return (randomized_value);
}

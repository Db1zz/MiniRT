/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:24:34 by gonische          #+#    #+#             */
/*   Updated: 2025/02/11 18:24:34 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt_math.h"
#include <math.h>

double	vec3_length_squared(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_length(t_vector v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vector	vec3_random(void)
{
	return ((t_vector){random_double(), random_double(), random_double()});
}

t_vector	vec3_random_range(double min, double max)
{
	return ((t_vector){
			random_double_range(min, max),
			random_double_range(min, max),
			random_double_range(min, max)});
}

t_vector	vec3_random_unit_vec(void)
{
	const double	epsilon = 1e-4;
	t_vector		random_vec;
	double			vec_lenght;

	while (true)
	{
		random_vec = vec3_random_range(-1, 1);
		vec_lenght = vec3_length_squared(random_vec);
		if (epsilon < vec_lenght && vec_lenght <= 1)
			return (vec3_div(random_vec, sqrt(vec_lenght)));
	}
}

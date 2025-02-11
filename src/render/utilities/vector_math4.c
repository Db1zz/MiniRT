/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:24:18 by gonische          #+#    #+#             */
/*   Updated: 2025/02/11 18:24:18 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vec3_cross(t_vector a, t_vector b)
{
	return (create_vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

t_vector	vec3_negate(t_vector a)
{
	return (create_vector(-a.x, -a.y, -a.z));
}

double	vec3_distance(t_vector a, t_vector b)
{
	double	x;

	x = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (x);
}

t_vector	vec3_random_on_hemisphere(const t_vector *sphere_normal_vec)
{
	double		dot_product;
	t_vector	random_unit_vec;

	random_unit_vec = vec3_random_unit_vec();
	dot_product = vec3_dot(random_unit_vec, *sphere_normal_vec);
	if (dot_product > 0.0)
		return (random_unit_vec);
	else
		return (vec3_invert(&random_unit_vec));
}

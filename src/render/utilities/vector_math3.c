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

#include <math.h> /* sqrt() | pow() */

double	vec3_length_squared(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_length(t_vector v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vector	vec3_cross(t_vector a, t_vector b)
{
	return ((t_vector){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}

t_vector	vec3_negate(t_vector a)
{
	return ((t_vector){-a.x, -a.y, -a.z});
}

double	vec3_distance(t_vector a, t_vector b)
{
	double	x;

	x = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (x);
}

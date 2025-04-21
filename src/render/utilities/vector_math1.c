/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:24:47 by gonische          #+#    #+#             */
/*   Updated: 2025/02/11 18:24:48 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "utils.h"
#include <math.h>

t_vector	vec3_div_vec3(t_vector v1, t_vector v2)
{
	return ((t_vector){div_c(v1.x, v2.x),
			div_c(v1.y, v2.y),
			div_c(v1.z, v2.z)});
}

t_vector	vec3_mult_vec3(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

t_vector	vec3_sub_vec3(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vector	vec3_add_vec3(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vector	vec3_normalize(t_vector vector)
{
	double	mag;

	mag = vec3_length(vector);
	if (mag == 0)
		return (vector);
	return ((t_vector){vector.x / mag, vector.y / mag, vector.z / mag});
}

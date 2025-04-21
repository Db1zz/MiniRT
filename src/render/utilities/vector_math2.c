/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:24:45 by gonische          #+#    #+#             */
/*   Updated: 2025/03/22 12:35:43 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vec3_div(t_vector vector, double val)
{
	return ((t_vector){vector.x / val, vector.y / val, vector.z / val});
}

t_vector	vec3_mult(t_vector vector, double val)
{
	return ((t_vector){vector.x * val, vector.y * val, vector.z * val});
}

t_vector	vec3_sub(t_vector vector, double val)
{
	return ((t_vector){vector.x - val, vector.y - val, vector.z - val});
}

t_vector	vec3_add(t_vector vector, double val)
{
	return ((t_vector){vector.x + val, vector.y + val, vector.z + val});
}

double	vec3_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

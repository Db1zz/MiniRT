/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:28:03 by gonische          #+#    #+#             */
/*   Updated: 2025/04/13 17:29:30 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt_math.h"
#include "vector.h"
#include "light.h"
#include "libft.h"

t_ray	create_ray(
	t_vector origin,
	t_vector direction,
	t_color color,
	double length)
{
	return ((t_ray){origin, direction, color, length});
}

t_vector	get_ray_direction(t_vector origin, t_vector endpoint)
{
	return (vec3_normalize(vec3_sub_vec3(endpoint, origin)));
}

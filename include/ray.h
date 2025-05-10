/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:57:57 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:57:57 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "object.h" /* t_object */
# include "aabb.h" /* t_aabb */
# include "vector.h" /* t_vector | functions */
# include "scene.h" /* t_scene */
# include "color.h" /* t_color | functions */
# include "hit_record.h" /* t_hit_record | functions */
# include "camera.h" /* t_camera | functions */

# include <stdbool.h>

/*
	// ====================== Typedefs ====================== //
*/
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_color		color;
	double		length;
}	t_ray;

typedef bool	(*t_ray_hit_shape_funp)(
					const t_ray *ray,
					const t_object *shape,
					t_hit_record *rec);
// Typedefs

/*
	// ====================== Functions ====================== //
*/

t_ray			create_ray(
					t_vector origin,
					t_vector direction,
					t_color color,
					double length);

t_vector		get_ray_direction(
					t_vector origin,
					t_vector endpoint);

t_color			ray_trace_bvh_color(
					const t_ray *ray,
					const t_bvh_node *tree,
					const t_scene *scene);

t_color			ray_trace_array_color(
					const t_ray *ray,
					const t_scene *scene);

// Functions

#endif // RAY_H

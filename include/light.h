/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:50:11 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 00:50:11 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h" /* t_color | functions */
# include "color.h"	/* t_color | functions */
# include "hit_record.h" /* t_hit_record */
# include "ray.h" /* t_ray */

/* Color ration min and max */
# define RATIO_MIN 0
# define RATIO_MAX 1

typedef struct s_amb_lighting
{
	double	ratio;
	t_color	color;
}	t_amb_lighting;

typedef struct s_light
{
	t_vector	pos;
	t_color		color;
	double		ratio;
	double		radius;
}	t_light;

double	calculate_specular_intensity(
			const t_light *light,
			const t_ray *camera_ray,
			const t_hit_record *hit_rec,
			double specular_reflection_coefficient);

double	calculate_diffuse_intensity(
			const t_light *light,
			const t_hit_record *shape_rec);

t_color	calculate_diffuse_color(
			const t_light *light,
			const t_hit_record *shape_rec);

t_color	apply_light_filter(
			const t_light *light,
			const t_hit_record *shape_rec);

t_color	compute_object_illumination(
			const t_ray *camera_ray,
			const t_scene *scene,
			const t_hit_record *shape_rec);

#endif // LIGHT_H
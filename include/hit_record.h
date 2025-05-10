/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:49:34 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 19:59:12 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_RECORD_H
# define HIT_RECORD_H

# include "vector.h" /* t_vector */
# include "color.h" /* t_color */

typedef struct s_hit_record
{
	t_vector		intersection_p;
	t_vector		normal;
	t_color			color;
	t_vector		ray_direction;
	double			ray_distance;
	bool			front_face;
}	t_hit_record;

void			init_hit_record(t_hit_record *rec);

t_hit_record	*get_closest_hit(
					t_hit_record *first,
					t_hit_record *second);

t_vector		hit_record_to_ray_origin(const t_hit_record *rec);

#endif // HIT_RECORD_H

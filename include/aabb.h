/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:52:52 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 13:52:52 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# include "vector.h" /* t_vector */
# include "interval.h" /* t_interval */

typedef struct s_aabb
{
	t_interval	interval[3];
}	t_aabb;

t_aabb	create_aabb_from_vectors(const t_vector *a, const t_vector *b);
t_aabb	create_aabb_from_aabb(const t_aabb *a, const t_aabb *b);
t_aabb	aabb_create_empty(void);

#endif // AABB_H
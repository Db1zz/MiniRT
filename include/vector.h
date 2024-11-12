/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:26:26 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 21:15:21 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#define VECTOR_MAX_SIZE 3

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

void	set_vector(t_vector *vector, float x, float y, float z);
int		str_to_vector(t_vector *vector, const char *vector_str);

#endif // VECTOR_H
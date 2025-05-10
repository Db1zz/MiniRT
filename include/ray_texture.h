/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:55:46 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 00:55:46 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TEXTURE_H
# define RAY_TEXTURE_H

# include "hit_record.h"
# include "object.h"

t_color	get_plane_color(
			const t_plane *plane,
			t_hit_record *rec);

#endif // RAY_TEXTURE_H
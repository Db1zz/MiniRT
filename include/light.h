/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:42:57 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 15:36:11 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
#define LIGHT_H

#include "pos.h"
#include "color.h"
#include "scene.h"

typedef struct s_amb_lighting
{
	double	ratio;
	t_color	color;
}	t_amb_lighting;

typedef struct s_light
{
	t_pos	pos;
	double	ratio;
	t_color	color;
}	t_amb_lighting;

void	create_light(t_scene *scene, const t_pos *pos,
			double ratio, const t_color *color);
void	create_amb_lightning(t_scene *scene,
			double ratio, const t_color *color);

#endif	// LIGHT_H

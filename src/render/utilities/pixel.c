/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:15 by gonische          #+#    #+#             */
/*   Updated: 2025/03/26 19:26:09 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "color.h"
#include "scene.h"
#include "mlx.h"

void	draw_pixel(t_scene *scene, int x, int y, t_color *color)
{
	mlx_pixel_put(scene->mlx, scene->win, x, y, rgb_to_int(color));
}

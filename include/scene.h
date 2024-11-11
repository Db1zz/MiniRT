/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:07:22 by gonische          #+#    #+#             */
/*   Updated: 2024/11/08 15:12:20 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "shapes.h"

typedef struct s_scene
{
	/*camera*/
	/*ambient light*/
	/*light sources*/
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_scene;

#endif	// SCENE_H

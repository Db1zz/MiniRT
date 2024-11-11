/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:44:09 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 17:37:49 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "shapes.h"
#include "scene.h"
#include "light.h"
#include <stdlib.h>

#define CYLINDER_ARGS 6
#define PLANE_ARGS 5
#define SPHERE_ARGS 3

int		normalize_vector(t_pos *vector);
t_scene	*parse_input(int argc, char **argv);

#endif // PARSER_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:35:12 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:35:12 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "scene.h" /* t_scene */
# include "render_bonus.h" /* t_render_workers_ctx | functions */

# ifdef __APPLE__
#  include "key_macos.h"
# elif __linux__
#  include "key_linux.h"
# endif

typedef struct s_minirt_ctx
{
	t_scene					scene;
	t_render_workers_ctx	workers;
}	t_minirt_ctx;

int	minirt_routine_bonus(int argc, char **argv);

#endif  //	MINIRT_BONUS_H
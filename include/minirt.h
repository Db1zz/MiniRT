/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:49:13 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 13:49:13 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "scene.h" /* t_scene */
# include "render.h" /* render_scene() */

# ifdef __APPLE__
#  include "key_macos.h"
# elif __linux__
#  include "key_linux.h"
# endif

typedef struct s_minirt_ctx
{
	t_scene	scene;
}	t_minirt_ctx;

int	minirt_routine(int argc, char **argv);

#endif // MINIRT_H    // fedia was herrr

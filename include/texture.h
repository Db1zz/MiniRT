/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:50:14 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 13:50:14 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# define TEXTURE_SC 20.0
# define BOARD_SIZE 50

typedef struct s_texture
{
	void	*img;
	void	*mlx;
	int		height;
	int		width;
	int		*pixels;
}	t_texture;

#endif // !TEXTURE_H

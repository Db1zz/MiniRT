/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:43:12 by gonische          #+#    #+#             */
/*   Updated: 2024/11/27 20:46:05 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* pseudo random function */
int	ft_rand(void)
{
	static unsigned long int	seed = 1;

	seed = seed * 1103515245 + 12345;
	return ((unsigned int)(seed / 65536) % 32768);
}

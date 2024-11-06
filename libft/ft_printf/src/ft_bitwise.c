/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:14:11 by gonische          #+#    #+#             */
/*   Updated: 2024/07/23 17:48:26 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_internal.h"

void	ft_set_bit(char *bit_set, char bit)
{
	*bit_set |= bit;
}

bool	ft_check_bit(char bit_set, char bit)
{
	return (bit_set & bit);
}

bool	ft_check_remove_bit(char *bit_set, char bit)
{
	bool	result;

	result = ft_check_bit(*bit_set, bit);
	if (result)
		*bit_set &= ~bit;
	return (result);
}

void	ft_adjust_bits(char *bit_set, char bits)
{
	*bit_set &= bits;
}

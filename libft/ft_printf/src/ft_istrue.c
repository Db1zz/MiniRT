/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:17:39 by gonische          #+#    #+#             */
/*   Updated: 2024/07/23 19:45:36 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_internal.h"

bool	ft_isspecifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%');
}

char	ft_isflag(char c)
{
	if (c == '-')
		return (MINUS_FLAG);
	else if (c == '0')
		return (ZERO_FLAG);
	else if (c == '.')
		return (DOT_FLAG);
	else if (c == '#')
		return (HASH_FLAG);
	else if (c == ' ')
		return (SPACE_FLAG);
	else if (c == '+')
		return (PLUS_FLAG);
	return (0);
}

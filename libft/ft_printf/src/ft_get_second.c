/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_second.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:06:27 by gonische          #+#    #+#             */
/*   Updated: 2024/07/23 19:45:18 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_internal.h"

t_disp_func	*ft_get_pattern(t_format *f)
{
	t_disp_func	*p;

	p = (t_disp_func *)ft_calloc(PATTERN_SIZE, sizeof(t_disp_func));
	if (p == NULL)
		return (NULL);
	if (f->width > 0 && ft_check_bit(f->flags, WIDTH_FLAG))
	{
		if (ft_check_bit(f->flags, MINUS_FLAG))
			p[5] = &ft_display_padding;
		else if (ft_check_bit(f->flags, ZERO_FLAG))
			p[2] = &ft_display_padding;
		else if (ft_check_bit(f->flags, WIDTH_FLAG))
			p[0] = &ft_display_padding;
	}
	p[1] = &ft_display_modifier;
	if (ft_check_bit(f->flags, DOT_FLAG))
		p[3] = &ft_display_precision;
	if (!(f->specifier == 's' && ft_check_bit(f->flags, DOT_FLAG)))
		p[4] = &ft_display_str;
	return (p);
}

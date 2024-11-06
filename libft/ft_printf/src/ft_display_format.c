/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:12:19 by gonische          #+#    #+#             */
/*   Updated: 2024/09/27 23:00:11 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_internal.h"

int	ft_display_padding(t_format *f, int fd)
{
	char	pad;
	int		counter;

	pad = ' ';
	counter = 0;
	if (f->width > 0)
		counter = f->width;
	if (ft_check_bit(f->flags, ZERO_FLAG))
		pad = '0';
	while (f->width-- > 0)
		ft_putchar_fd(pad, fd);
	return (counter);
}

int	ft_display_modifier(t_format *f, int fd)
{
	ft_putstr_fd(f->special_str, fd);
	return (ft_strlen(f->special_str));
}

int	ft_display_precision(t_format *f, int fd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (f->specifier == 's')
	{
		while (f->output_str[i] && f->precision-- > 0)
		{
			ft_putchar_fd(f->output_str[i++], fd);
			counter++;
		}
	}
	else
	{
		while (f->precision-- > 0)
		{
			ft_putchar_fd('0', fd);
			counter++;
		}
	}
	return (counter);
}

int	ft_display_str(t_format *f, int fd)
{
	if (f->output_str)
	{
		ft_putstr_fd(f->output_str, fd);
		if (f->specifier == 'c' && f->output_str[0] == 0)
		{
			ft_putchar_fd('\0', fd);
			return (1);
		}
		return (ft_strlen(f->output_str));
	}
	return (0);
}

int	ft_display_format(t_format *f, int fd)
{
	int			i;
	t_disp_func	*pattern;
	int			result;

	i = -1;
	result = 0;
	if (f->output_str)
	{
		ft_calc_width_precision(f);
		pattern = ft_get_pattern(f);
		if (pattern)
		{
			while (++i < PATTERN_SIZE)
				if (pattern[i])
					result += pattern[i](f, fd);
			free(pattern);
		}
	}
	else
		result += ft_printstr("(null)", fd);
	return (result);
}

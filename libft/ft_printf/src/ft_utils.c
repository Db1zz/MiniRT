/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:19:35 by gonische          #+#    #+#             */
/*   Updated: 2024/09/27 22:52:34 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_internal.h"

void	ft_calc_width_precision(t_format *f)
{
	int	output_size;

	output_size = ft_strlen(f->output_str);
	if (f->specifier == 'c' && f->output_str[0] == '\0')
		output_size++;
	if (f->specifier == 's')
	{
		if (output_size >= f->precision && ft_check_bit(f->flags, DOT_FLAG))
			f->width -= f->precision;
		else
			f->width -= output_size;
	}
	else
	{
		f->precision -= output_size;
		f->width -= (ft_strlen(f->special_str) + output_size);
		if (f->precision > 0)
			f->width -= f->precision;
	}
}

void	ft_validate_flags(t_format *f)
{
	int			i;
	const char	flags[][2] = {
	{'c', MINUS_FLAG | WIDTH_FLAG},
	{'%', MINUS_FLAG | WIDTH_FLAG},
	{'p', MINUS_FLAG | WIDTH_FLAG},
	{'s', MINUS_FLAG | WIDTH_FLAG | DOT_FLAG},
	{'d', MINUS_FLAG | WIDTH_FLAG | DOT_FLAG | ZERO_FLAG
		| SPACE_FLAG | PLUS_FLAG},
	{'i', MINUS_FLAG | WIDTH_FLAG | DOT_FLAG | ZERO_FLAG
		| SPACE_FLAG | PLUS_FLAG},
	{'u', MINUS_FLAG | ZERO_FLAG | WIDTH_FLAG | DOT_FLAG},
	{'x', MINUS_FLAG | ZERO_FLAG | HASH_FLAG | WIDTH_FLAG | DOT_FLAG},
	{'X', MINUS_FLAG | ZERO_FLAG | HASH_FLAG | WIDTH_FLAG | DOT_FLAG}};

	i = 0;
	while (flags[i] && flags[i][0] != f->specifier)
		i++;
	if (flags[i][0] == f->specifier)
		ft_adjust_bits(&f->flags, flags[i][1]);
}

size_t	ft_get_number_size(int64_t number)
{
	size_t		result;
	int64_t		num;

	result = 1;
	num = number;
	if (number < 0)
		num = number * -1;
	while (num > 9)
	{
		num /= 10;
		result++;
	}
	return (result);
}

int	ft_printstr(char *str, int fd)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i++], fd);
		c++;
	}
	return (c);
}

int	ft_get_hex_size(uint64_t hex)
{
	int	i;

	i = 1;
	while (hex / 16)
	{
		hex /= 16;
		i++;
	}
	return (i);
}

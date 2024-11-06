/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:18:28 by gonische          #+#    #+#             */
/*   Updated: 2024/07/23 19:42:39 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_internal.h"

void	ft_get_specifier(const char *str, t_format *f)
{
	int	i;

	i = 1;
	f->specifier = 0;
	while (str[i])
	{
		if (ft_isspecifier(str[i]))
		{
			f->specifier = str[i];
			f->size = i;
			break ;
		}
		else if (!ft_isflag(str[i]) && !ft_isdigit(str[i]))
			break ;
		i++;
	}
}

void	ft_get_special_str(t_format *f)
{
	if (ft_check_bit(f->flags, PLUS_FLAG) && f->special_str[0] != '-')
		f->special_str[0] = '+';
	else if (ft_check_bit(f->flags, SPACE_FLAG) && f->special_str[0] != '-')
		f->special_str[0] = ' ';
	if (ft_check_bit(f->flags, HASH_FLAG)
		&& (f->specifier == 'x' || f->specifier == 'X')
		&& f->output_str[0] != '0')
	{
		f->special_str[0] = '0';
		f->special_str[1] = f->specifier;
	}
}

void	ft_get_output_str(va_list *data, t_format *f)
{
	if (f->specifier == 's')
	{
		f->output_str = va_arg(*data, char *);
		return ;
	}
	f->output_str = (char *)ft_calloc(1, MAX_BUFFER_SIZE);
	if (f->output_str == NULL)
		return ;
	else if (f->specifier == 'c')
		f->output_str[0] = (char)va_arg(*data, int);
	else if (f->specifier == 'p')
		ft_convert_to_address_str(f, va_arg(*data, uint64_t));
	else if (f->specifier == 'd')
		ft_convert_to_number_str(f, va_arg(*data, int));
	else if (f->specifier == 'i')
		ft_convert_to_number_str(f, va_arg(*data, int));
	else if (f->specifier == 'u')
		ft_convert_to_number_str(f, va_arg(*data, uint32_t));
	else if (f->specifier == 'x' || f->specifier == 'X')
		ft_convert_to_hex_str(f, va_arg(*data, uint32_t));
	else if (f->specifier == '%')
		f->output_str[0] = '%';
	ft_get_special_str(f);
}

void	ft_get_flags(const char *str, t_format *f)
{
	int		i;
	char	flag;

	i = 0;
	while (str[i] && str[i] != f->specifier)
	{
		flag = ft_isflag(str[i]);
		if (flag)
		{
			ft_set_bit(&f->flags, flag);
			if (str[i] == '.' && ft_isdigit(str[i + 1]))
			{
				f->precision = ft_atoi(&str[i + 1]);
				i += ft_get_number_size(f->precision);
			}
		}
		else if (ft_isdigit(str[i]))
		{
			f->width = ft_atoi(&str[i]);
			i += ft_get_number_size(f->width) - 1;
			ft_set_bit(&f->flags, WIDTH_FLAG);
		}
		i++;
	}
	ft_validate_flags(f);
}

t_format	*ft_get_format_data(const char *str, va_list *data)
{
	t_format	*result;

	result = (t_format *)ft_calloc(1, sizeof(t_format));
	if (result == NULL)
		return (NULL);
	ft_get_specifier(str, result);
	result->special_str = (char *)ft_calloc(10, sizeof(char));
	if (!result->specifier || !result->special_str)
	{
		free(result);
		return (NULL);
	}
	ft_get_flags(str, result);
	ft_get_output_str(data, result);
	return (result);
}

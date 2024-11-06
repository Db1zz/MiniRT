/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:35 by gonische          #+#    #+#             */
/*   Updated: 2024/09/27 23:00:30 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Headers for project
*/
#include "../include/ft_printf.h"
#include "../include/ft_internal.h"

#include <stdio.h>

/*
	Project functions
*/
int	ft_format_parser(const char *str, va_list *data, int *printed_c, int fd)
{
	int			result;
	t_format	*format;

	result = 0;
	format = ft_get_format_data(str, data);
	if (format)
	{
		*printed_c += ft_display_format(format, fd);
		result = format->size;
		if (format->specifier != 's')
			free(format->output_str);
		free(format->special_str);
		free(format);
		return (result);
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	const int	fd = STDOUT_FILENO;
	va_list		data;
	size_t		i;
	int			printed_c;

	i = 0;
	printed_c = 0;
	if (!str)
		return (0);
	va_start(data, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], fd);
			printed_c++;
		}
		else if (str[i] == '%' && str[i + 1])
			i += ft_format_parser(&str[i], &data, &printed_c, fd);
		i++;
	}
	va_end(data);
	return (printed_c);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list		data;
	size_t		i;
	int			printed_c;

	i = 0;
	printed_c = 0;
	if (!str)
		return (0);
	va_start(data, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], fd);
			printed_c++;
		}
		else if (str[i] == '%' && str[i + 1])
			i += ft_format_parser(&str[i], &data, &printed_c, fd);
		i++;
	}
	va_end(data);
	return (printed_c);
}


// int main(void)
// {
// 	int x = printf(" NULL %s NULL \n", NULL);
// 	int y = ft_printf(" NULL %s NULL \n", NULL);
// 	printf("x: %d\n y: %d\n", x, y);
// };

/*
	Tests
*/
// int main(void)
// {
// 	int a = 42;
//     // Basic Specifiers
//     printf("Original: %c\n", 'A');
//	   ft_printf("Custom:   %c\n", 'A');

//     printf("Original: %s\n", "Hello, World!");
//     ft_printf("Custom:   %s\n", "Hello, World!");

//     printf("Original: %p\n", (void*)&a);
//     ft_printf("Custom:   %p\n", (void*)&a);

//     printf("Original: %d\n", 123);
//     ft_printf("Custom:   %d\n", 123);

//     printf("Original: %i\n", -123);
//     ft_printf("Custom:   %i\n", -123);

//     printf("Original: %u\n", 123U);
//     ft_printf("Custom:   %u\n", 123U);

//     printf("Original: %x\n", 0x1a3f);
//     ft_printf("Custom:   %x\n", 0x1a3f);

//     printf("Original: %X\n", 0x1A3F);
//     ft_printf("Custom:   %X\n", 0x1A3F);

//     printf("Original: %%\n");
//     ft_printf("Custom:   %%\n");

//     // Width and Precision
// 		printf("Width and Precision\n");
//     printf("Original: %10d\n", 123);
//     ft_printf("Custom:   %10d\n", 123);

//     printf("Original: %.5d\n", 123);
//     ft_printf("Custom:   %.5d\n", 123);

//     printf("Original: %10.5d\n", 123);
//     ft_printf("Custom:   %10.5d\n", 123);

//     printf("Original: %10s\n", "Hello");
//     ft_printf("Custom:   %10s\n", "Hello");

//     printf("Original: %.5s\n", "Hello, World!");
//     ft_printf("Custom:   %.5s\n", "Hello, World!");

//     printf("Original: %10.5s\n", "Hello, World!");
//     ft_printf("Custom:   %10.5s\n", "Hello, World!");

//     printf("Original: %10.5x\n", 0x1a3f);
//     ft_printf("Custom:   %10.5x\n", 0x1a3f);

//     // Flags
//     printf("Original: %-10d\n", 123);
//     ft_printf("Custom:   %-10d\n", 123);

//     printf("Original: %010d\n", 123);
//     ft_printf("Custom:   %010d\n", 123);

//     printf("Original: %#x\n", 0x1a3f);
//     ft_printf("Custom:   %#x\n", 0x1a3f);

//     printf("Original: %#X\n", 0x1A3F);
//     ft_printf("Custom:   %#X\n", 0x1A3F);

//     printf("Original: % d\n", 123);
//     ft_printf("Custom:   % d\n", 123);

//     printf("Original: %+d\n", 123);
//     ft_printf("Custom:   %+d\n", 123);

//     printf("Original: %+010d\n", 123);
//     ft_printf("Custom:   %+010d\n", 123);

//     printf("Original: %-#10x\n", 0x1a3f);
//     ft_printf("Custom:   %-#10x\n", 0x1a3f);

//     printf("Original: % 10.5d\n", 123);
//     ft_printf("Custom:   % 10.5d\n", 123);    
// 	printf("Original: %c\n", 'A');
//     ft_printf("Custom:   %c\n", 'A');

//     printf("Original: %s\n", "Hello, World!");
//     ft_printf("Custom:   %s\n", "Hello, World!");

//     printf("Original: %p\n", (void*)&a);
//     ft_printf("Custom:   %p\n", (void*)&a);

//     printf("Original: %d\n", 123);
//     ft_printf("Custom:   %d\n", 123);

//     printf("Original: %i\n", -123);
//     ft_printf("Custom:   %i\n", -123);

//     printf("Original: %u\n", 123U);
//     ft_printf("Custom:   %u\n", 123U);

//     printf("Original: %x\n", 0x1a3f);
//     ft_printf("Custom:   %x\n", 0x1a3f);

//     printf("Original: %X\n", 0x1A3F);
//     ft_printf("Custom:   %X\n", 0x1A3F);

//     printf("Original: %%\n");
//     ft_printf("Custom:   %%\n");

//     // Width and Precision
//     printf("Original: %10d\n", 123);
//     ft_printf("Custom:   %10d\n", 123);

//     printf("Original: %.5d\n", 123);
//     ft_printf("Custom:   %.5d\n", 123);

//     printf("Original: %10.5d\n", 123);
//     ft_printf("Custom:   %10.5d\n", 123);

//     printf("Original: %10s\n", "Hello");
//     ft_printf("Custom:   %10s\n", "Hello");

//     printf("Original: %.5s\n", "Hello, World!");
//     ft_printf("Custom:   %.5s\n", "Hello, World!");

//     printf("Original: %10.5s\n", "Hello, World!");
//     ft_printf("Custom:   %10.5s\n", "Hello, World!");

//     printf("Original: %10.5x\n", 0x1a3f);
//     ft_printf("Custom:   %10.5x\n", 0x1a3f);

//     // Flags
//     printf("Original: %-10d\n", 123);
//     ft_printf("Custom:   %-10d\n", 123);

//     printf("Original: %010d\n", 123);
//     ft_printf("Custom:   %010d\n", 123);

//     printf("Original: %#x\n", 0x1a3f);
//     ft_printf("Custom:   %#x\n", 0x1a3f);

//     printf("Original: %#X\n", 0x1A3F);
//     ft_printf("Custom:   %#X\n", 0x1A3F);

//     printf("Original: % d\n", 123);
//     ft_printf("Custom:   % d\n", 123);

//     printf("Original: %+d\n", 123);
//     ft_printf("Custom:   %+d\n", 123);

//     printf("Original: %+010d\n", 123);
//     ft_printf("Custom:   %+010d\n", 123);

//     printf("Original: %-#10x\n", 0x1a3f);
//     ft_printf("Custom:   %-#10x\n", 0x1a3f);
// 	return (0);
// }

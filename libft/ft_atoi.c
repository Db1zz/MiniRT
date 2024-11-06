/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:14:30 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:45:15 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	neg;

	result = 0;
	i = 0;
	neg = 1;
	while (isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
		result = (result * 10) + (str[i++] - 48);
	return (result * neg);
}

/*
// Tests
#include <stdlib.h> // used to check which input atoi can handle
#include <stdio.h>
#include <limits.h>

void	test(char *str)
{
	int	atoi_res;
	int ft_atoi_res;

	ft_atoi_res = ft_atoi(str);
	atoi_res = atoi(str);
	if (atoi_res == ft_atoi_res)
		printf("PASS!\n");
	else
		printf("ERROR: ft_atoi_res: %d atoi_res: %d\n", ft_atoi_res, atoi_res);
}

int	main()
{
	test("123");
	test("123.asdasd");
	test("0");
	test("-0");
	test("-----10");
	test("-10");
	test("+10");
	test("++++10");
	test("+0000000000123");
	test("+-0000000000123");
	test("-+0000000000123");
	test("\177 128");
	test("2147483647");
	test("2247483649");
	test("-2147483648");
	test("-2347483648");
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:56:30 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:50:21 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*
// Testing zone 
#include <stdio.h>

void	test(int value, int expected_result)
{
	int	result;

	result = ft_isprint(value);
	if (result == expected_result)
		printf("PASS! ft_isprint: %d\n", result);
	else
		printf("FAILED! ft_isprint: %d, expected: \
				%d\n", result, expected_result);
}

int	main(void)
{
	test('1', 1);
	test('9', 1);
	test('a', 1);
	test('.', 1);
	test('~', 1);
	test(31, 0);
	test(127, 0);

	return (0);
}
*/
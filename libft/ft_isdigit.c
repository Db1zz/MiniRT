/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:52:15 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:50:18 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
// Testing zone 
#include <stdio.h>

void	test(int value, int expected_result)
{
	int	result;

	result = ft_isdigit(value);
	if (result == expected_result)
		printf("PASS! ft_isdigit: %d\n", result);
	else
		printf("FAILED! ft_isdigit: %d, expected: \
				%d\n", result, expected_result);
}

int	main(void)
{
	test('1', 1);
	test('9', 1);
	test('a', 0);
	test('.', 0);
	test('~', 0);

	return (0);
}
*/
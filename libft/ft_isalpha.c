/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:40:59 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:50:08 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// Testing zone 
/*
#include <stdio.h>
#include <ctype.h>

void	test(int value)
{
	int	result;
	int	expected_result;

	result = ft_isalpha(value);
	expected_result = isalpha(value);
	if (result >= expected_result)
		printf("PASS! ft_isalpha: %d\n", result);
	else
		printf("FAILED! ft_isalpha: %d, expected: \
				%d\n", result, expected_result);
}

int	main(void)
{
	test('a');
	test('z');
	test('A');
	test('Z');
	test('1');

	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:21:11 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:50:35 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static size_t	itarr_size(long int n)
{
	size_t	result;

	result = 1;
	while (n > 9)
	{
		n /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	long int	v;
	char		*result;
	size_t		len;
	int			i;

	len = 0 + (n < 0);
	v = n;
	if (len)
		v = v * -1;
	len += itarr_size(v);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = len - 1;
	while (i >= (0 + (n < 0)))
	{
		result[i--] = (v % 10) + '0';
		v /= 10;
	}
	if (n < 0)
		result[0] = '-';
	result[len] = '\0';
	return (result);
}

// Tests
/*
#include <stdio.h>
void	test(int to_print)
{
	char	*result = ft_itoa(to_print);
	printf("got:	  %s\n", result);
	printf("expected: %d\n", to_print);
	free(result);
}

int	main(void)
{
	test(INT_MIN);
	test(INT_MAX);
	test(0);
	test(-1);
	test(01);
	return (0);
}
*/
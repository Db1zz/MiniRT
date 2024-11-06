/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:52:57 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:47:02 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (dest);
	if (dest > src)
	{
		while (n-- > 0)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
	{
		i = -1;
		while (++i < n)
			((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}

// abcd = a 1
// cd.. = c 3
// abab
// abcd

// Tests
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char test_arr[] = "Hello World!";
	ft_memmove(&test_arr[6], &test_arr[0], 5);
	printf("Result: %s\n", test_arr);
	return (0);
}
*/
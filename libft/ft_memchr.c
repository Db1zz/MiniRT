/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:09:22 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:46:36 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (NULL);
}

// Tests
/*
#include <stdio.h>

void	test(const void *s, int c, size_t n)
{
	char * res;

	res = (char *)ft_memchr(s, c, n);
	printf("%s\n", res);
	
}

int	main(void)
{
	test("Space Ship", 'h', 10);
	test("Space Ship", 'S', 10);
	return (0);
}
*/
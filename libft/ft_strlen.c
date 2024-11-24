/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:28:11 by gonische          #+#    #+#             */
/*   Updated: 2024/11/24 19:48:56 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*
// Testin Zone
#include <stdio.h>

int	main(void)
{
	printf("Test 1: %d\n", ft_strlen("Hello World!\n"));
	printf("Test 2: %d\n", ft_strlen("\n"));
	printf("Test 3: %d\n", ft_strlen(""));
	return (0);
}
*/
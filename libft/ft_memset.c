/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:33:53 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:47:12 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
	return (s);
}

/*
// Tests
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strdup(char *src)
{
	int		len;
	char	*result;

	len = ft_strlen(src);
	result = (char *)malloc(len);
	ft_strcpy(result, src);
	return (result);
}

void	test(void *s, int c, size_t n)
{
	char	*str1;

	str1 = ft_strdup((char *)s);
	ft_memset((void *)str1, c, n);
	printf("Result: %s\n", str1);
}

int	main(void)
{
	test("0123456", '-', 1);
}
*/
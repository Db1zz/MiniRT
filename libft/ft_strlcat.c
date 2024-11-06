/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:12:02 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:29:28 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	i;

	i = 0;
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (dstsize + ft_strlen(src));
	while ((dstlen + i) < (dstsize - 1) && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + ft_strlen(src));
}

// Tests
/*
	For tests compile this programm with:
		 cc -lbsd ft_strlcat.c ft_memcpy.c ft_strlen.c
*/
/*
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

void	test(char *dest, char *src, size_t dest_len)
{
	char *ft_strlcat_dest = (char *)malloc(dest_len + 1);
	ft_strlcat_dest[dest_len] = '\0';

	char *strlcat_dest = (char *)malloc(dest_len + 1);
	strlcat_dest[dest_len] = '\0';

	ft_memcpy(ft_strlcat_dest, dest, dest_len);
	ft_memcpy(strlcat_dest, dest, dest_len);

	size_t	ft_strlcat_result = ft_strlcat(ft_strlcat_dest, src, dest_len);
	size_t	strlcat_result = strlcat(strlcat_dest, src, dest_len);
	if (ft_strlcat_result == strlcat_result)
		printf("PASS: %zu | %zu!\n", ft_strlcat_result, strlcat_result);
	else
		printf("FAILED: ft_strlcat: %s [%zu], strlcat: %s [%zu]\n", 
			   ft_strlcat_dest, ft_strlcat_result, strlcat_dest, strlcat_result);
}

int	main(void)
{
	test("Hello", " World!", 14);
	test("", " World!", 14);
	test("World!", "", 0);
	test("", "World!", 15);
	test("Hello", " World!", 0);
	test("pqrstuvwxyz", "abcd", 1);
	// printf("%zu\n",ft_strlcat("pqrstuvwxyz", "abcd", 1));
	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:20:50 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:48:12 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = ft_strlen(src);
	if (dstsize == 0)
		return (result);
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (result);
}

// Tests
/*
	For tests compile this programm with cc -lbsd ft_strlcpy.c ft_strlen.c
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

void	test(size_t dest_len, const char *src)
{
	char *ft_strlcpy_dest = (char *)malloc(dest_len + 1);
	ft_strlcpy_dest[dest_len] = '\0';

	char *strlcpy_dest = (char *)malloc(dest_len + 1);
	strlcpy_dest[dest_len] = '\0';

	size_t ft_strlcpy_res = ft_strlcpy(ft_strlcpy_dest, src, dest_len);
	size_t ftrlcpy_res = strlcpy(strlcpy_dest, src, dest_len);
	if (ft_strlcpy_res == ftrlcpy_res)
		printf("PASS!\n");
	else
		printf("FAILED: ft_strlcat: %s [%zu], strlcat: %s [%zu]\n", 
			   ft_strlcpy_dest, ft_strlcpy_res, strlcpy_dest, ftrlcpy_res);
	free(ft_strlcpy_dest);
	free(strlcpy_dest);
}

int	main(void)
{
	test(10, "Hello World!\n");
	test(0, "Hello World!\n");
	test(10, "");
	test(0, "");
	test(0, "");
	return (0);
}
*/
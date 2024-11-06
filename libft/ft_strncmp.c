/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:58:20 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 22:41:18 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
// Tests
#include <string.h>
#include <stdio.h>

void	test(char *str1, char *str2, size_t n)
{
	int	ft_strncmp_res;
	int strncmp_res;

	ft_strncmp_res = ft_strncmp(str1, str2, n);
	strncmp_res = strncmp(str1, str2, n);
	if (ft_strncmp_res == strncmp_res)
		printf("PASS!\n");
	else
		printf("FAILED: ft_strncmp %d != strncmp %d\n", \
				ft_strncmp_res, strncmp_res);
}

int	main(void)
{
	test("aboba", "aboba", 3);
	test("aboba", "abobac", 3);
	test("aboba", "abobac", 6);
	test("aboba", "abobac", 0);
	test("", "abobac", 0);
	test("abobac", "", 0);
	test("", "abobac", 10);
	test("abobac", "", 10);
}
*/
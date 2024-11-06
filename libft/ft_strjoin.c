/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:17:36 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:29:28 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result || (s1 == 0 && s2 == 0))
		return (NULL);
	ft_memcpy(result, s1, s1_len);
	ft_memcpy(result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}

/*
// Tests
#include <stdio.h>

void	test(char const *s1, char const *s2, char const *expected)
{
	size_t	s1_len = ft_strlen(s1);
	char	*result = ft_strjoin(s1, s2);
	size_t	s2_len = ft_strlen(s2);
	if (!ft_memcmp(result, expected, s1_len + s2_len))
		printf("PASS!\n");
	else
		printf("FAILED: Got %s, Expected %s%s\n", 
			   result, s1, s2);
	free(result);
}

int	main(void)
{
	test("456", "", "456");
	test("456", "123", "456123");
	test("", "", "");
	test("0", "123", "0123");
	test("", "123", "123");
	return (0);
}
*/
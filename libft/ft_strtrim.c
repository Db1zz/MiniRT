/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:08:17 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:48:56 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	while (ft_strchr(set, s1[end]) && end >= start)
		end--;
	result = (char *)malloc((end - start) + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)(s1 + start), (end - start) + 2);
	return (result);
}
/*
// Tests
#include <stdio.h>

void	test(char const *s1, char const *set, char const *expected)
{
	char	*result;

	result = ft_strtrim(s1, set);
	if (!ft_strncmp(result, expected, ft_strlen(expected)))
		printf("PASS!\n");
	else
		printf("FAILED: Got '%s', Expected '%s'\n", result, expected);
	free(result);
}

int	main(void)
{
	test("dascdasdMy name is Simonasdasdasd adasdasd asdcas", "asd", 
		"cdasdMy name is Simonasdasdasd adasdasd asdc");

	return (0);
}
*/
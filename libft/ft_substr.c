/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:04:35 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:49:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	return (result);
}

// Tests
/*
#include <stdio.h>

void	test(char const *string, unsigned int start, 
			 size_t len, char const *expected)
{
	char	*result = ft_substr(string, start, len);
	int		cmp_res = ft_memcmp(expected, result, len);
	if(!cmp_res)
		printf("PASS! %s\n", result);
	else
		printf("FAILED: Got %s, Expected %s | CMP_RES: %d\n", 
				result, expected, cmp_res);
	free(result);
}

int	main(void)
{
	test("Hello World!", 6, 6, "World!");
}
*/
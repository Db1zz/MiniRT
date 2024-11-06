/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:08:09 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 22:41:17 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && i + j < len)
		{
			if (little[j] != big[i + j])
				break ;
			j++;
		}
		if (little[j] == '\0')
			return (&((char *)big)[i]);
		i++;
	}
	return (NULL);
}

// Bad Tests
/*
#include <string.h> // Where is the strnstr function?
#include <stdio.h>

void	test(const void *s1, const void *s2, size_t n)
{
	char *ft_strnstr_res;

	ft_strnstr_res = ft_strnstr(s1, s2, n);
	printf("%s\n", ft_strnstr_res);
}

int	main(void)
{
	test("aboba", "bob", 4);
	test("zxccxcxz", "cxz", 8);
	return (0);
}
*/
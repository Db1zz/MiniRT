/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:30:56 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:51:41 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			break ;
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

/*
// Tests
#include <stdio.h>

void	test(char *str, int c)
{
	char	*res;

	res = ft_strchr(str, c);
	if (res)
		printf("RES == %c\n", *res);
	else
		printf("RES == NULL\n");
}

int	main(void)
{
	test("lol", 'o');
	test("lol", 'i');
	test("asdasdasd\0", 'i');

	return (0);
}
*/
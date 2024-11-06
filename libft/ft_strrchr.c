/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:51:24 by gonische          #+#    #+#             */
/*   Updated: 2024/09/19 22:41:15 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			result = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (result);
}

/*
// Tests
#include <stdio.h>

void	test(char *str, int c)
{
	char	*res;

	res = ft_strrchr(str, c);
	if (res)
		printf("RES == %c\n", *res);
	else
		printf("RES == NULL\n");

}
int	main(void)
{
	test("lolo", 'o');
	test("lol", 'i');

	return (0);
}
*/
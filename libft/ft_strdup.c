/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:58:19 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:47:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	size_t	len;
	char	*result;

	len = ft_strlen(src);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, src, len);
	result[len] = '\0';
	return (result);
}

/*
// Tests
#include <stdio.h>
#include <string.h>

void	test(char *to_dup)
{
	char	*strdup_res = strdup(to_dup);
	char	*ft_strdup_res = ft_strdup(to_dup);

	if (!strncmp(strdup_res, ft_strdup_res, strlen(to_dup)))
		printf("PASS!\n");
	else
		printf("FAILED: strdup_res[%s] ft_strdup_res[%s]\n",
			  strdup_res, ft_strdup_res);
}

int	main(void)
{
	test("Hello World!");
	return (0);
}
*/
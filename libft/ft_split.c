/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:53:58 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 19:51:36 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(char const *s, char delimeter)
{
	size_t	i;
	size_t	result;
	int		is_word;

	i = 0;
	result = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] == delimeter && is_word == 1)
		{
			result++;
			is_word = 0;
		}
		else if (s[i] != delimeter && is_word == 0)
			is_word = 1;
		i++;
	}
	if (is_word == 1)
		result++;
	return (result);
}

static char	*alloc_word(char const *s, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	if (result)
		ft_memcpy(result, s, len);
	result[len] = '\0';
	return (result);
}

static char	**free_matrix(char **mat, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(mat[i++]);
	return (NULL);
}

static char	**fill_matrix(char const *s, char delimeter, char **dest, size_t n)
{
	size_t		i;
	char const	*start;
	int			is_word;

	i = 0;
	is_word = 0;
	while (i < n)
	{
		if ((*s == delimeter || !(*s)) && is_word == 1)
		{
			dest[i++] = alloc_word(start, s - start);
			if (!dest[i - 1])
				break ;
			is_word = 0;
		}
		if (*s != delimeter && is_word == 0)
		{
			start = s;
			is_word = 1;
		}
		s++;
	}
	if (!dest[i - 1])
		return (free_matrix(dest, i - 1));
	return (dest);
}

char	**ft_split(char const *s, char delimeter)
{
	char	**result;
	size_t	matrix_len;

	matrix_len = count_words(s, delimeter);
	result = (char **)malloc(sizeof(char *) * (matrix_len + 1));
	if (!result)
		return (NULL);
	result[matrix_len] = NULL;
	if (matrix_len && !fill_matrix(s, delimeter, result, matrix_len))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

// Tests
/*
#include <stdio.h>

void	test_count_words(char const *s, char delimeter, int expected)
{
	int	result = count_words(s, delimeter);
	if (result == expected)
		printf("PASS!\n");
	else
		printf("FAILED test_count_words: Got %d, Expected %d\n",
				result, expected);
}

void	print_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	printf("[");
	while (matrix[i])
	{
		printf("%s, ", matrix[i]);
		free(matrix[i++]);
	}
	printf("]\n");
	free(matrix);
}

void	test_ft_split(char const *s, char delimeter)
{
	char	**result = ft_split(s, delimeter);
	print_matrix(result);
}

int	main(void)
{
	test_count_words("lolcabobachuesos", 'c', 3);
	test_count_words("", 'c', 0);
	test_count_words("abc", 'c', 1);
	test_ft_split("lolcabobachuesos", 'c');
	test_ft_split("lol", 'c');
	test_ft_split("", 'c');
	test_ft_split("rnd1\0asdasd\0dfskgfdg\0sadfasdf\0", '\0');
	test_ft_split("\0rnd1\0asdasd\0dfskgfdg\0sadfasdf\0", '\0');
	test_ft_split("      split       this for   me  !       ", ' ');
}
*/
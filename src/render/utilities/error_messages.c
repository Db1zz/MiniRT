/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:19:39 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 14:19:39 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

#include <stdlib.h> /* NULL */

const char	*get_standard_error_to_msg(t_errorn errorn)
{
	static const char	*msgs[] = {
		"Function parameter == NULL",
		"Malloc failed",
		"Failed to obtain FD from open()",
		"Invalid function arguments"};

	return (msgs[errorn - STANDARD_ERROR_MIN]);
}

const char	*get_parser_errorn_to_msg(t_errorn errorn)
{
	static const char	*msgs[] = {
		"Light->ratio should be in range 0 - 1.0",
		"Type converstion failed",
		"Cannot convert non-numeric string to a number",
		"ft_split failed to split string",
		"Cannot convert string to color",
		"ft_atoi failed to convert string to a number",
		"Failed to normalize vector",
		"Unknown object specifier",
		"Multiple instances if an object",
		"Cannot convert string to vector",
		"Camera not found",
		"Exceeding limits for objects",
		"Invalid file extension, expected: .rt",
		"Invalid file path for the texture",
		"An invalid number of parameters was provided to init the entity"};

	if (errorn < PARSER_ERRN_MIN || errorn > PARSER_ERRN_MAX)
		return (NULL);
	return (msgs[errorn - PARSER_ERRN_MIN]);
}

const char	*get_minirt_errorn_to_msg(t_errorn errorn)
{
	static const char	*msgs[] = {
		"Incorrect amount of arguments. Try: ./miniRT scenes/test.rt",
		"Color values should be in range 0 - 255",
		"FOV value should be in range 0 - 180",
	};

	return (msgs[errorn - MINIRT_ERRORN_MIN]);
}

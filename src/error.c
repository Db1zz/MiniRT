#include "ft_error.h"
#include <stdio.h>

static const char	*parser_errorn_to_msg(t_error errorn)
{
	static const char	*msgs[] = {
		"Light->ratio should be in range 0 - 1.0",
		"Type converstion failed",
		"Cannot convert non-numeric string to vector",
		"ft_split failed to split string",
		"Cannot convert string to color",
		"ft_atoi failed to convert string to a number",
		"Failed to normalize vector",
		"Unknown object specifier"
	};

	if (errorn < PARSER_ERRN_MIN || errorn > PARSER_ERRN_MAX)
		return (NULL);
	return (msgs[errorn - PARSER_ERRN_MIN]);
}

static const char	*minirt_errorn_to_msg(t_error errorn)
{
	static const char	*msgs[] = {
		"Color values should be in range 0 - 255",
		"FOV value should be in range 0 - 180",
	};

	return (msgs[errorn - MINIRT_ERRORN_MIN]);
}

static const char	*standard_error_to_msg(t_error errorn)
{
	static const char	*msgs[] = {
		"Function parameter == NULL",
		"Malloc failed",
	};

	return (msgs[errorn - STANDARD_ERROR_MIN]);
}

void	ft_perror(t_error errorn, const char *func)
{
	const char	*msg;

	if (errorn == ERR_NO_ERROR)
		return ;
	msg = NULL;
	if (errorn >= MINIRT_ERRORN_MIN && errorn <= MINIRT_ERRORN_MAX)
		msg = minirt_errorn_to_msg(errorn);
	else if (errorn >= PARSER_ERRN_MIN && errorn <= PARSER_ERRN_MAX)
		msg = parser_errorn_to_msg(errorn);
	else if (errorn >= STANDARD_ERROR_MIN && errorn <= STANDARD_ERROR_MAX)
		msg = standard_error_to_msg(errorn);
	if (msg == NULL)
		printf("Error in %s: incorrect error number\n", __func__);
	else
		printf("Error in %s: %s\n", func, msg);
}

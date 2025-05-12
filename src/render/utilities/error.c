/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:24:53 by gonische          #+#    #+#             */
/*   Updated: 2025/05/07 18:31:20 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include <stdio.h>

void	ft_perror(t_errorn errorn, const char *func)
{
	const char	*msg;

	if (errorn == ERR_NO_ERROR)
		return ;
	msg = NULL;
	if (errorn >= STANDARD_ERROR_MIN && errorn <= STANDARD_ERROR_MAX)
		msg = get_standard_error_to_msg(errorn);
	else if (errorn >= PARSER_ERRN_MIN && errorn <= PARSER_ERRN_MAX)
		msg = get_parser_errorn_to_msg(errorn);
	else if (errorn >= MINIRT_ERRORN_MIN && errorn <= MINIRT_ERRORN_MAX)
		msg = get_minirt_errorn_to_msg(errorn);
	if (msg == NULL)
		printf("Error in %s: incorrect error number\n", __func__);
	else
		printf("Error in %s: %s\n", func, msg);
}

void	ft_display_error(const t_error *error)
{
	ft_perror(error->errorn, error->func);
}

void	set_error(t_error *error, t_errorn errorn, const char *func)
{
	error->errorn = errorn;
	error->func = func;
}

t_error	create_error(t_errorn errorn, const char *func)
{
	return ((t_error){errorn, func});
}

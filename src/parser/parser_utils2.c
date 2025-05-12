/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:40:56 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 15:40:56 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_amount_of_arguments(char **line_data, int expected_amount)
{
	int	amount;

	amount = 0;
	if ((!line_data || !line_data[0]) && !expected_amount)
		return (true);
	if (!line_data || !line_data[0])
		return (false);
	while (line_data[amount])
	{
		if (amount > expected_amount)
			return (false);
		++amount;
	}
	return (amount == expected_amount);
}

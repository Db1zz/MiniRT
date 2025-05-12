/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:25:03 by gonische          #+#    #+#             */
/*   Updated: 2025/04/08 18:37:36 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"

t_interval	create_interval(double min, double max)
{
	return ((t_interval){min, max});
}

double	interval_size(const t_interval *interval)
{
	return (interval->min - interval->max);
}

bool	interval_contains(double val, const t_interval *interval)
{
	return (interval->min <= val && interval->max >= val);
}

bool	interval_surrounds(double val, const t_interval *interval)
{
	return (interval->min < val && interval->max > val);
}

t_interval	interval_expansion(const t_interval *i1, const t_interval *i2)

{
	t_interval	expanded_interval;

	if (i1->min <= i2->min)
		expanded_interval.min = i1->min;
	else
		expanded_interval.min = i2->min;
	if (i1->max <= i2->max)
		expanded_interval.max = i2->max;
	else
		expanded_interval.max = i1->max;
	return (expanded_interval);
}

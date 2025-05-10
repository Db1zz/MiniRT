/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:55:09 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 13:55:09 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include <stdbool.h>

typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

t_interval	create_interval(double min, double max);
double		interval_size(const t_interval *interval);
bool		interval_contains(double val, const t_interval *interval);
bool		interval_surrounds(double val, const t_interval *interval);
double		interval_clamp(const t_interval *interval, double x);
t_interval	interval_expansion(const t_interval *i1, const t_interval *i2);

#endif	// INTERVAL_H
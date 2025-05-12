/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:16:31 by gonische          #+#    #+#             */
/*   Updated: 2025/05/12 15:57:33 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include <stdlib.h>

struct timeval	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

time_t	get_minutes_diff(
	const struct timeval *start_time,
	const struct timeval *end_time)
{
	const time_t	ms_start = get_time_in_milliseconds(start_time);
	const time_t	ms_end = get_time_in_milliseconds(end_time);

	return ((((ms_end - ms_start) / 1000) / 60) % 60);
}

time_t	get_seconds_diff(
	const struct timeval *start_time,
	const struct timeval *end_time)
{
	const time_t	ms_start = get_time_in_milliseconds(start_time);
	const time_t	ms_end = get_time_in_milliseconds(end_time);

	return (((ms_end - ms_start) / 1000) % 60);
}

time_t	get_milliseconds_diff(
	const struct timeval *start_time,
	const struct timeval *end_time)
{
	const time_t	ms_start = get_time_in_milliseconds(start_time);
	const time_t	ms_end = get_time_in_milliseconds(end_time);

	return ((ms_end - ms_start) % 1000);
}

time_t	get_time_in_milliseconds(const struct timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

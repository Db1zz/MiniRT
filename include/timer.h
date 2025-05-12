/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:48:45 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:48:45 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

# include <sys/time.h> /* timeval | gettimeofday */

struct timeval	get_time(void);

time_t	get_minutes_diff(
			const struct timeval *start_time,
			const struct timeval *end_time);

time_t	get_seconds_diff(
			const struct timeval *start_time,
			const struct timeval *end_time);

time_t	get_milliseconds_diff(
			const struct timeval *start_time,
			const struct timeval *end_time);

time_t	get_time_in_milliseconds(
			const struct timeval *time);

#endif  // TIMER_H
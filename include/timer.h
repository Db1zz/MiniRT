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

struct timeval	getTime(void);

time_t			getMinutesDiff(
					const struct timeval *start_time,
					const struct timeval *end_time);

time_t			getSecondsDiff(
					const struct timeval *start_time,
					const struct timeval *end_time);

time_t			getMilisecondsDiff(
					const struct timeval *start_time,
					const struct timeval *end_time);

time_t			getMicrosecondsDiff(
					const struct timeval *start_time,
					const struct timeval *end_time);

time_t			getTimeInMilliseconds(
					const struct timeval *start_time);

#endif  // TIMER_H
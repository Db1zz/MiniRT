#ifndef TIMER_H
# define TIMER_H

#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval getTime();

time_t getMinutesDiff(
	const struct timeval *start_time,
	const struct timeval *end_time);

time_t getSecondsDiff(
	const struct timeval *start_time,
	const struct timeval *end_time);

time_t getMilisecondsDiff(
	const struct timeval *start_time,
	const struct timeval *end_time);

time_t getMicrosecondsDiff(
	const struct timeval *start_time,
	const struct timeval *end_time);

time_t getTimeInMilliseconds(
	const struct timeval *start_time);

#endif  // TIMER_H
#ifndef TIMER_H
# define TIMER_H

#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval getTime();

long getMinutesDiff(const struct timeval *start_time, const struct timeval *end_time);
long getSecondsDiff(const struct timeval *start_time, const struct timeval *end_time);
long getMilisecondsDiff(const struct timeval *start_time, const struct timeval *end_time);
long getMicrosecondsDiff(const struct timeval *start_time, const struct timeval *end_time);

#endif  // TIMER_H
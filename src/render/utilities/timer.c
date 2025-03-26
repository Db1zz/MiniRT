#include "timer.h"
#include <sys/time.h>

struct timeval getTime() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time);
}

time_t getMinutesDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return (((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time)) / 1000) / 60) % 60;
}

time_t getSecondsDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return ((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time)) / 1000) % 60;
}

time_t getMilisecondsDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return (((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time))) % 1000);
}

time_t getMicrosecondsDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return ((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time)) % 1000);
}

time_t getTimeInMilliseconds(const struct timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}
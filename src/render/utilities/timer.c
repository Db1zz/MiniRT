#include "timer.h"
#include <sys/time.h>

struct timeval getTime() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time);
}

long getMinutesDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return (((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time)) / 1000 / 1000) / 60) % 60;
}

long getSecondsDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return ((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time)) / 1000 / 1000) % 60;
}

long getMilisecondsDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return (((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time)) / 1000) % 1000);
}

long getMicrosecondsDiff(const struct timeval *start_time, const struct timeval *end_time) {
  return ((getTimeInMilliseconds(end_time) - getTimeInMilliseconds(start_time)) % 1000);
}

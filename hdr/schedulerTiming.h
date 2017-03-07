#ifndef __SCHEDULER_TIMING_H__
#define __SCHEDULER_TIMING_H__


#include <time.h>
#include "ADTDefs.h"
typedef struct timespec timespec;

timespec AddTimeToPeriod (timespec _t1, timespec _t2);
int isBefore (timespec _newTaskTime, timespec _oldTaskTime);
timespec ConvertmsToSpec (size_t _period);
timespec CalculateDelta (timespec _t1, timespec _t2);
int TimeToSleep (timespec _sleepTime); /*nanosleep*/
timespec CurrentTime( clockid_t _clk_id);


#endif


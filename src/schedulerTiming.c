#include "vector.h"
#include "scheduler2.h"
#include "heap_gen.h"
#include "taskCreator.h"
#include <stdlib.h>
#include <stdio.h>
#include "check.h"
#include <time.h>
#define ONE_THOUSAND 1000
#define HUNDRED_THOUSAND 100000
#define SLEEP_SUCCEEDED 0
#define SLEEP_ERROR -1 
#define MILIARD 1000000000
#define MILLION 1000000


timespec CurrentTime( clockid_t _clk_id)
{
	 timespec currentTime;
	 clock_gettime(_clk_id, &currentTime);
	 return currentTime;
}
/***********************************************************************************************************************/
timespec AddTimeToPeriod (timespec _t1, timespec _t2)
{
	timespec result;
	result.tv_sec = _t1.tv_sec + _t2.tv_sec;
	result.tv_nsec = (_t1.tv_nsec + _t2.tv_nsec) % MILIARD;
	result.tv_sec= (result.tv_sec+ result.tv_nsec )/ MILIARD;
	/*result.tv_sec = _t1.tv_sec + _t2.tv_sec;
	result.tv_nsec = _t1.tv_nsec + _t2.tv_nsec;*/
	return result;
}	
/***********************************************************************************************************************/
int isBefore (timespec _newTaskTime, timespec _oldTaskTime)
{
	if(_newTaskTime.tv_sec  >  _oldTaskTime.tv_sec)
	{
		return 0;
	}
	else if (_newTaskTime.tv_sec ==  _oldTaskTime.tv_sec  && _newTaskTime.tv_nsec >  _oldTaskTime.tv_nsec)
	{
		return 0;
	}
	return 1;
}

/***********************************************************************************************************************/
timespec ConvertmsToSpec (size_t _period)
{
	
    timespec convert;
    convert.tv_sec=  (time_t)(_period/ONE_THOUSAND);
    convert.tv_nsec = (_period% ONE_THOUSAND) * MILLION;
    return convert;
}
/***********************************************************************************************************************/

timespec CalculateDelta (timespec _t1, timespec _t2)
{
    timespec delta;
    delta.tv_sec= _t1.tv_sec - _t2.tv_sec;
    delta.tv_nsec = _t1.tv_nsec - _t2.tv_nsec;
    return delta;
}

/***********************************************************************************************************************/

int TimeToSleep (timespec _sleepTime) /*nanosleep*/
{
	
	timespec ts;
	nanosleep(&_sleepTime, &ts) == SLEEP_SUCCEEDED ? SLEEP_SUCCEEDED : SLEEP_ERROR;
	
}








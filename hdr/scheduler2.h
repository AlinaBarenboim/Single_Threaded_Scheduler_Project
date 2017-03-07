#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include "heap_gen.h"
#include "schedulerTiming.h"
#include "taskCreator.h"
#include <time.h>
#include "ADTDefs.h"



typedef struct PeriodicExecutor PeriodicExecutor;

struct PeriodicExecutor
{
	Heap* m_tasks;
	const char* m_name;
	int m_pause;
	clockid_t m_clk_id;
	size_t m_magicNum;
};
	
PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clock_t _clk_id);
void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);
int PeriodicExecutor_Add(PeriodicExecutor* _executor, Task _task, void* _context, size_t _period_ms);
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);/*Loop while there is a task, no pause, check current time and sleep if need*/
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor);

#endif


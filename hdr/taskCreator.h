#ifndef __TASK_CREATOR_H__
#define __TASK_CREATOR_H__
#include "ADTDefs.h"

/*TODO change name of h file*/
typedef int(*Task)(void*_context);
typedef struct TaskObj TaskObj;

struct TaskObj
{
	Task m_task;
	timespec m_period;
 	void* m_context;
	timespec m_lastRunTime;
	clockid_t m_clk_id;
	

};

void SetLastRunTime (TaskObj* _task);
TaskObj* CreateTask (Task _task, size_t _period, void* _context, clockid_t _clk_id);
void TaskDestroy (Task* _task);
int ExecuteTask (TaskObj* _task);
timespec (NextRunTime (TaskObj* _task));
timespec (PrevRunTime (TaskObj* _task));

#endif

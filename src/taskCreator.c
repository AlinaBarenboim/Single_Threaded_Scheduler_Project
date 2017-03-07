
#include "vector.h"
#include "scheduler2.h"
#include "heap_gen.h"
#include "taskCreator.h"
#include <stdlib.h>
#include <stdio.h>
#include "check.h"
#include <time.h>


TaskObj* CreateTask (Task _task, size_t _period, void* _context, clockid_t _clk_id) /*context can be null*/
{
	timespec period;
	TaskObj* newTask = NULL;
	CHECK_ARGUMENTS(_task, NULL, NULL);
	newTask = (TaskObj*)malloc(sizeof(TaskObj));
	CHECK_ARGUMENTS(newTask, NULL, NULL);
	newTask->m_lastRunTime.tv_sec = 0;
	newTask->m_lastRunTime.tv_nsec = 0;
	period = ConvertmsToSpec (_period);
	newTask->m_period = period;
	newTask->m_context = _context;
	newTask->m_task = _task;
	newTask->m_clk_id = _clk_id;
	return newTask;
}
/***********************************************************************************************************************/
void TaskDestroy (Task* _task)
{
	CHECK_ARGUMENTS_VOID (_task, NULL);
	free(_task);
}
/***********************************************************************************************************************/
timespec NextRunTime (TaskObj* _task)
{	

	return AddTimeToPeriod (_task->m_period, _task->m_lastRunTime);
}
/***********************************************************************************************************************/
timespec (PrevRunTime (TaskObj* _task))
{
	return _task->m_lastRunTime;
}
/***********************************************************************************************************************/
int ExecuteTask (TaskObj* _task) /*returns 1 when task should be rescheduled or 0 if not*/
{
	CHECK_ARGUMENTS(_task, NULL, 0);
	int result = 0;
	result = _task->m_task(_task->m_context);
	SetLastRunTime( _task);
	return result;
}
/***********************************************************************************************************************/
void SetLastRunTime (TaskObj* _task)
{
	/*CHECK_ARGUMENTS_VOID(_task, NULL);*/
	_task->m_lastRunTime = CurrentTime(_task->m_clk_id);

}




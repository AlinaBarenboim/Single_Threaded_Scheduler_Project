#include "heap_gen.h"
#include "vector.h"
#include "scheduler2.h"
#include <stdlib.h>
#include <stdio.h>
#include "check.h"
#include <time.h>
#define VECTOR_INITIAL_SIZE 100
#define BLOCK_SIZE 50
#define MAGIC 0xDEADD00D
#define NOT_MAGIC 0
#define PAUSE 1
#define NOT_PAUSE 0

int isNewNotBeforeExs  (timespec _newTaskTime, timespec _existingTaskTime) /*time*/
{
	if(_newTaskTime.tv_sec  <  _existingTaskTime.tv_sec)
	{
		return 0;
	}
	else if (_newTaskTime.tv_sec ==  _existingTaskTime.tv_sec  && _newTaskTime.tv_nsec <  _existingTaskTime.tv_nsec)
	{
		return 0;
	}
	return 1;
}

/***********************************************************************************************************************/
 int NewTaskPriorityLower (TaskObj* _newTask, TaskObj* _oldTask)
{
	return isNewNotBeforeExs (NextRunTime (_newTask), NextRunTime(_oldTask));
}
/***********************************************************************************************************************/

PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clock_t _clk_id)
{
	PeriodicExecutor* executor = NULL;
	
	CHECK_ARGUMENTS (_name, NULL, NULL);
	
	executor = (PeriodicExecutor*)malloc(sizeof(PeriodicExecutor));
	CHECK_ARGUMENTS (executor, NULL, NULL);
	executor->m_tasks = HeapBuild(Vector_Create( VECTOR_INITIAL_SIZE, BLOCK_SIZE) , (LessComparator)NewTaskPriorityLower);
	CHECK_ARGUMENTS (executor->m_tasks, NULL, NULL);
	executor->m_pause = NOT_PAUSE;
	executor->m_clk_id = _clk_id;
	executor->m_magicNum = MAGIC;
	return executor;
}

/***********************************************************************************************************************/

void PeriodicExecutor_Destroy(PeriodicExecutor* _executor)
{
	Vector* vec;
	if (NULL == _executor && _executor->m_magicNum == MAGIC)
	{
		vec = (HeapDestroy(_executor->m_tasks));
		Vector_Destroy(&vec, (void(*)(void*))(TaskDestroy ) );
		_executor->m_magicNum = NOT_MAGIC;
		free (_executor);
	}
}

/***********************************************************************************************************************/
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor)
{
	CHECK_ARGUMENTS( _executor, NULL, 0);
	_executor->m_pause == 1 ? PAUSE : NOT_PAUSE;	
}
/***********************************************************************************************************************/
int PeriodicExecutor_Add(PeriodicExecutor* _executor, Task _task, void* _context, size_t _period_ms)
{
	
	int result = 0;
	TaskObj* addTask = NULL;
	CHECK_ARGUMENTS( _executor, NULL, 0);
	addTask = CreateTask (_task, _period_ms, &_context,  _executor->m_clk_id);
	CHECK_ARGUMENTS( addTask, NULL, 0);
	if (HeapInsert(_executor->m_tasks, (void*) addTask) == VECTOR_SUCCESS)
	{
		return 1;
	}
return 0;	
}

/***********************************************************************************************************************/

/*
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor)
{
	TaskObj* runTask = NULL;
	timespec nextRunTime;
	timespec currTime;
	CHECK_ARGUMENTS (_executor, NULL, 0);

	while( HeapExtractMax(_executor->m_tasks, (void**) &runTask) == VECTOR_SUCCESS)
	{
		nextRunTime = NextRunTime(runTask);
		currTime = CurrentTime(_executor->m_clk_id);
		if (ExecuteTask(runTask) == 0)
		{
			TaskDestroy (&runTask->m_task);

		}
		if(isNewNotBeforeExs (nextRunTime, currTime))
		{
			TimeToSleep(CalculateDelta(nextRunTime, currTime));
		}
	
		else
		{
		 	HeapInsert(_executor->m_tasks, (void*) runTask) ;
		}
		printf("pause = %d\n", _executor->m_pause);
		printf ("%d\n", runTask->m_period);
		printf ("%d\n",runTask->m_lastRunTime);
		if(_executor->m_pause == PAUSE)
		{
			break;
		}
	}

	return 0;
}
*/

size_t PeriodicExecutor_Run(PeriodicExecutor* _executor)
{
	TaskObj* taskObj = NULL;	
	timespec nextRunTime;
	timespec currTime;
	
	CHECK_ARGUMENTS (_executor, NULL, 0);
	
	_executor->m_pause = 0;

	while(ERR_OK == HeapExtractMax(_executor->m_tasks, (void**) &taskObj))
	{
		nextRunTime = NextRunTime(taskObj);
		currTime = CurrentTime(_executor->m_clk_id);
		if(isNewNotBeforeExs(nextRunTime, currTime))
		{
			TimeToSleep(CalculateDelta(nextRunTime, currTime));
		}		
		
		if(0 == ExecuteTask(taskObj))
		{
			TaskDestroy(taskObj);
		}	
		else
		{	
			HeapInsert(_executor->m_tasks, taskObj);
		}
		
		printf("paused = %d\n", _executor->m_pause);
		if(_executor->m_pause!= 0)
		{
			break;
		}
	}

	return 1;
}


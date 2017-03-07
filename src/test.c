#include "vector.h"
#include "scheduler2.h"
#include "heap_gen.h"
#include <stdlib.h>
#include <stdio.h>
#include "check.h"
#include <time.h>
#include "mu_test.h"



/*---------------------------------------------------------------*/

int ActionOne(int* _num)
{
	static int i = 5;	
	printf("ActionOne function. Num is %d\n", i);

	return i--;
}

int ActionTwo(int* _num)
{
	static int j = 4;	
	printf("ActionTwo function. Num is %d\n", j);

	return j--;
}

int ActionThree(PeriodicExecutor* _executor)
{
	static int l = 4;	
	printf("ActionThree function. Num is %d\n", l);
	PeriodicExecutor_Pause(_executor);

	return l--;
}

/*---------------------------------------------------------------*/

UNIT(creation)
	PeriodicExecutor* executor = NULL;
	executor = PeriodicExecutor_Create("namename", CLOCK_REALTIME);
	ASSERT_THAT(executor != NULL);
END_UNIT

UNIT(double_destruction)
	PeriodicExecutor* executor = NULL;
	executor = PeriodicExecutor_Create("namename", CLOCK_REALTIME);
	PeriodicExecutor_Destroy(executor);
	PeriodicExecutor_Destroy(executor);
	ASSERT_THAT(1 == 1);
END_UNIT

UNIT(insertion)
	PeriodicExecutor* executor = NULL;
	int num = 3;
	executor = PeriodicExecutor_Create("namename", CLOCK_REALTIME);
	ASSERT_THAT(PeriodicExecutor_Add(executor, (Task) ActionOne, &num, 1000) == VECTOR_SUCCESS);
	PeriodicExecutor_Destroy(executor);
	ASSERT_THAT(1 == 1);
END_UNIT

UNIT(one_task_job)
	PeriodicExecutor* executor = NULL;
	int num = 3;
	executor = PeriodicExecutor_Create("namename", CLOCK_REALTIME);
	ASSERT_THAT(PeriodicExecutor_Add(executor, (Task) ActionOne, &num, 1000) == VECTOR_SUCCESS);
	ASSERT_THAT(PeriodicExecutor_Run(executor) == 0);
	PeriodicExecutor_Destroy(executor);
	ASSERT_THAT(1 == 1);
END_UNIT

UNIT(two_tasks_job)
	PeriodicExecutor* executor = NULL;
	int num = 3;
	executor = PeriodicExecutor_Create("namename", CLOCK_REALTIME);
	ASSERT_THAT(PeriodicExecutor_Add(executor, (Task) ActionTwo, &num, 2000) == 1);
	ASSERT_THAT(PeriodicExecutor_Add(executor, (Task) ActionOne, &num, 500) ==1);
	ASSERT_THAT(PeriodicExecutor_Run(executor) == 1);
	PeriodicExecutor_Destroy(executor);
	ASSERT_THAT(1 == 1);
END_UNIT

UNIT(pause)
	PeriodicExecutor* executor = NULL;
	int num = 3;
	executor = PeriodicExecutor_Create("namename", CLOCK_REALTIME);
	ASSERT_THAT(PeriodicExecutor_Add(executor, (Task) ActionTwo, &num, 2000) == 1);
	ASSERT_THAT(PeriodicExecutor_Add(executor, (Task) ActionOne, &num, 500) == 1);
	ASSERT_THAT(PeriodicExecutor_Add(executor, (Task) ActionThree, executor, 6000) == 1);
	PeriodicExecutor_Run(executor);
	sleep(5);
	ASSERT_THAT(PeriodicExecutor_Run(executor) != 0);
	PeriodicExecutor_Destroy(executor);
	ASSERT_THAT(1 == 1);
END_UNIT


TEST_SUITE(Generic Vector Tests)
	//TEST(creation)
	//TEST(double_destruction)
	//TEST(insertion)
	//TEST(one_task_job)
	//TEST(two_tasks_job)
	TEST(pause)
END_SUITE

/*
int i =5;

int TestTaskFunc (void* _context)
{
	
	printf ("\n%d\n",i);
	i--;
	return i;
}


/*******************************************TEST_HASH***************************************************************
UNIT(Test_Create)
PeriodicExecutor * ex;	


ex= PeriodicExecutor_Create("name", CLOCK_REALTIME);
ASSERT_THAT (ex != NULL);
END_UNIT


UNIT(Test_Destroy)
PeriodicExecutor * ex;	

ex= PeriodicExecutor_Create("name", CLOCK_REALTIME);
PeriodicExecutor_Destroy(ex);
ASSERT_THAT (1==1);
END_UNIT

/*
UNIT(Test_Add_One)
PeriodicExecutor * ex;	
ex= PeriodicExecutor_Create("name", CLOCK_REALTIME);
ASSERT_THAT (PeriodicExecutor_Add(ex, (Task)TestTaskFunc ,NULL, 1000) == 1);
PeriodicExecutor_Destroy(ex);

END_UNIT

UNIT(Test_Run_One)
PeriodicExecutor * ex;	
ex= PeriodicExecutor_Create("name", CLOCK_REALTIME);
ASSERT_THAT (PeriodicExecutor_Add(ex, (Task)TestTaskFunc ,(void*)2, 1000) == 1);
ASSERT_THAT (PeriodicExecutor_Run(ex) == 1);
PeriodicExecutor_Destroy(ex);

END_UNIT 

UNIT(Test_Run_Few)
PeriodicExecutor * ex;	
ex= PeriodicExecutor_Create("name", CLOCK_REALTIME);
ASSERT_THAT (PeriodicExecutor_Add(ex, (Task)TestTaskFunc ,(void*)2, 1000000) == 1);
ASSERT_THAT (PeriodicExecutor_Add(ex, (Task)TestTaskFunc ,(void*)3, 9000000) == 1);
ASSERT_THAT (PeriodicExecutor_Run(ex) == 1);
PeriodicExecutor_Destroy(ex);

END_UNIT 






TEST_SUITE(Scheduler Test)
	//TEST(Test_Create)
	//TEST(Test_Destroy)
	//TEST(Test_Add_One)
	//TEST(Test_Run_One)
	TEST(Test_Run_Few)
END_SUITE
*/





#include <string.h>
#include <stdlib.h>
#include "cfg.h"
#include "cdefBF537.h"
#include "ucos_ii.h"
#include "bsp.h"

#define TASK1_PRIO 10
#define TASK2_PRIO 15
#define ROOT_PRIO  20

#define STACKSIZE 1024

unsigned long AppStack[APPSTACKSIZE];
OS_STK stack[STACKSIZE];
OS_STK stack1[STACKSIZE];
OS_STK stack2[STACKSIZE];
OS_EVENT *sem;


/*
 * Task 1
 */
void task1(void *arg) {
INT8U OS_result;

OS_result = 0;
INT8U  err= 0;

while(1) {

        OSSemPend(sem, 0, &err   );

	BSP_toggleLED (6);
	OSTimeDly(50);
	printf("1 ");
        INT8U pp =  OSSemPost(sem);
}
}


/*
 * Task 2
 */
void task2(void *arg) {
INT8U OS_result;


OS_result = 0;
INT8U err =0;

while(1) {

        OSSemPend(sem, 0, &err   );

	BSP_toggleLED (6);
	OSTimeDly(50);
	printf("2 ");
        INT8U pp2 =  OSSemPost(sem);
}
}


/*
 * Root Task: main task
 */
void rootTask(void *arg) {
INT8U OS_result;

OS_result = 0;
sem = OSSemCreate(1);

if((OS_result = OSTaskCreateExt(task1, 
				(void *)NULL, 
				&stack1[STACKSIZE-1], 
				TASK1_PRIO, 
				TASK1_PRIO, 
				&stack1[0], 
				STACKSIZE, 
				(void *)0, 
				0 )))
		printf("OSTaskCreateExt task1 failed\n");

if ((OS_result = OSTaskCreateExt(task2, 
				(void *)NULL, 
				&stack2[STACKSIZE-1], 
				TASK2_PRIO, 
				TASK2_PRIO, 
				&stack2[0], 
				STACKSIZE, 
				(void *)0, 
				0 )))
		printf("OSTaskCreateExt task2 failed\n");
while(1) {
	
	

	OSTimeDly(100);
}
}


int main() {
INT8U OS_result;

BSP_initLED();

OSInit();

printf("uC/OS II for BF537\n");

if ((OS_result = OSTaskCreateExt(rootTask, 
				(void *)NULL, 
				&stack[STACKSIZE-1], 
				ROOT_PRIO, 
				ROOT_PRIO, 
				&stack[0], 
				STACKSIZE, 
				(void *)0, 
				0 )))
		printf("OSTaskCreateExt rootTask failed\n");

OSStart();

return(0);
}


/* app_init():
 * Called by OSInitHookEnd(void) in os_cpu_c.c
 */
void app_init(void) {

/* Initialization of tick timer */
BSP_CoreTmrInit();
}


/* register_handler_ex():
 * This function is called a few times from os_cpu_c.c.
 */
void register_handler_ex(int inum,void (*func)(void),int mode) {

switch(inum) {
	case 6:
		*pEVT6 = func;
		*pIMASK |= EVT_IVTMR;	
		break;
	case 14:
		*pEVT14 = func;
		*pIMASK |= EVT_IVG14;	
		break;
	default:
	      printf("ERROR: unexpected inum value\n");
}
}


int Cstart(void) {

main();

return(0);
}

#include <string.h>
#include <stdlib.h>
#include "cfg.h"
#include "cdefBF537.h"
#include "ucos_ii.h"
#include "bsp.h"

#define TASK1_PRIO 18
#define TASK2_PRIO 17
#define TASK3_PRIO 16
#define TASK4_PRIO 15
#define TASK5_PRIO 14

#define ROOT_PRIO  20

#define STACKSIZE 1024

unsigned long AppStack[APPSTACKSIZE];
OS_STK stack[STACKSIZE];
OS_STK stack1[STACKSIZE];
OS_STK stack2[STACKSIZE];
OS_STK stack3[STACKSIZE];
OS_STK stack4[STACKSIZE];
OS_STK stack5[STACKSIZE];


OS_EVENT *sem1;
OS_EVENT *sem2;
OS_EVENT *sem3;
OS_EVENT *sem4;
OS_EVENT *sem5;

int counter1;
int counter2;

/*
 * Task 1
 */
void task1(void *arg) {
INT8U OS_result;

OS_result = 0;

INT8U  err= 0;


while(1) {

	
        OSSemPend(sem5, 0, &err   );
        OSSemPend(sem1, 10, &err   );
	if( err == OS_TIMEOUT){
	  OSSemPost(sem5);
	  goto fin;
	}
	BSP_setLED (1);
	OSTimeDly(10);
	BSP_clrLED (1);
	OSSemPost(sem1);
	OSSemPost(sem5);
OSTimeDly(100);
 fin:;
	printf("1 ");

}


}


/*
 * Task 2
 */
void task2(void *arg) {
INT8U OS_result;

OS_result = 0;
INT8U  err= 0;

while(1) {

        OSSemPend(sem1, 0, &err   );
        OSSemPend(sem2, 10, &err   );
	if( err == OS_TIMEOUT){
	  OSSemPost(sem1);
	  goto fin;
	}
	BSP_setLED (2);
	OSTimeDly(10);
	BSP_clrLED (2);
	OSSemPost(sem2);
	OSSemPost(sem1);
OSTimeDly(100);
 fin:;
	printf("2 ");

}


}


/*
 * Task 3
 */
void task3(void *arg) {
INT8U OS_result;

OS_result = 0;
INT8U  err= 0;

while(1) {
        OSSemPend(sem2, 0, &err   );
        OSSemPend(sem3, 10, &err   );
	if( err == OS_TIMEOUT){
	  OSSemPost(sem2);
	  goto fin;
	}
	BSP_setLED (3);
	OSTimeDly(10);
	BSP_clrLED (3);
	OSSemPost(sem3);
	OSSemPost(sem2);
OSTimeDly(100);
 fin:;
	printf("3 ");

 }
}


/*
 * Task 4
 */
void task4(void *arg) {
INT8U OS_result;

OS_result = 0;
INT8U  err= 0;

while(1) {
        OSSemPend(sem3, 0, &err   );
        OSSemPend(sem4, 10, &err   );
	if( err == OS_TIMEOUT){
	  OSSemPost(sem3);
	  goto fin;
	}
	BSP_setLED (4)
;
	OSTimeDly(10);
	BSP_clrLED (4);
	OSSemPost(sem4);
	OSSemPost(sem3);
OSTimeDly(100);
 fin:;
	printf("4 ");

 }
}


/*
 * Task 5
 */
void task5(void *arg) {
INT8U OS_result;

OS_result = 0;
INT8U  err= 0;

while(1) {
        OSSemPend(sem4, 0, &err   );
        OSSemPend(sem5, 10, &err   );
	if( err == OS_TIMEOUT){
	  OSSemPost(sem4);
	  goto fin;
	}
	BSP_setLED (5);
	OSTimeDly(10);
	BSP_clrLED (5);
	OSSemPost(sem5);
	OSSemPost(sem4);
OSTimeDly(100);
 fin:;
	printf("5 ");

 }
}

/*
 * Root Task: main task
 */
void rootTask(void *arg) {
INT8U OS_result;

OS_result = 0;
sem1 = OSSemCreate(0);
sem2 = OSSemCreate(0);
sem3 = OSSemCreate(0);
sem4 = OSSemCreate(0);
sem5 = OSSemCreate(0);

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

if ((OS_result = OSTaskCreateExt(task3, 
				(void *)NULL, 
				&stack3[STACKSIZE-1], 
				TASK3_PRIO, 
				TASK3_PRIO, 
				&stack3[0], 
				STACKSIZE, 
				(void *)0, 
				0 )))
		printf("OSTaskCreateExt task3 failed\n");

if ((OS_result = OSTaskCreateExt(task4, 
				(void *)NULL, 
				&stack4[STACKSIZE-1], 
				TASK4_PRIO, 
				TASK4_PRIO, 
				&stack4[0], 
				STACKSIZE, 
				(void *)0, 
				0 )))
		printf("OSTaskCreateExt task4 failed\n");

if ((OS_result = OSTaskCreateExt(task5, 
				(void *)NULL, 
				&stack5[STACKSIZE-1], 
				TASK5_PRIO, 
				TASK5_PRIO, 
				&stack5[0], 
				STACKSIZE, 
				(void *)0, 
				0 )))
		printf("OSTaskCreateExt task5 failed\n");
/*
	OSTimeDly(100);
        OSSemPost(sem5);

	OSTimeDly(100);
        OSSemPost(sem4);

	OSTimeDly(100);
        OSSemPost(sem3);

	OSTimeDly(100);
        OSSemPost(sem2);

	OSTimeDly(100);
        OSSemPost(sem1);
*/

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

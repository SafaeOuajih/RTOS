#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cfg.h"
#include "cdefBF537.h"
#include "ucos_ii.h"
#include "bsp.h"


#define BLINK_PRIO (OS_LOWEST_PRIO-3)
#define ROOT_PRIO  (OS_LOWEST_PRIO-2)

#define STACKSIZE 1024

#define PROMPT printf("ucos%% ")

void myscans(char *str);
void compute();

unsigned long AppStack[APPSTACKSIZE];
OS_STK stack[STACKSIZE];
OS_STK stackblink[STACKSIZE];
OS_STK stacki[10][STACKSIZE];


/*
 * Task
 */
void task(void *arg) {
INT8U OS_result;

OS_result = 0;

while(1) {

}
}


/*
 * blink
 */
void blink(void *arg) {
INT8U OS_result;

OS_result = 0;

OSTaskNameSet(OS_PRIO_SELF, (INT8U *)"blink\t", &OS_result);

while(1) {

}
}


/*
 * Root Task: main task
 */
void rootTask(void *arg) {
INT8U OS_result;

OS_result = 0;

OSStatInit(); 

OSTaskNameSet(OS_PRIO_SELF, (INT8U *)"rootTask", &OS_result);

if ((OS_result = OSTaskCreateExt(blink, 
				(void *)NULL, 
				&stackblink[STACKSIZE-1], 
				BLINK_PRIO, 
				BLINK_PRIO, 
				&stackblink[0], 
				STACKSIZE, 
				(void *)0, 
				OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR ))) {
		printf("OSTaskCreateExt blink failed\n");
}

while(1) {

}
}


int main() {
INT8U OS_result;

OS_result = 0;

BSP_initLED();

OSInit();

printf("uC/OS II shell for BF537\n");

if ((OS_result = OSTaskCreateExt(rootTask, 
				(void *)NULL, 
				&stack[STACKSIZE-1], 
				ROOT_PRIO, 
				ROOT_PRIO, 
				&stack[0], 
				STACKSIZE, 
				(void *)0, 
				OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR )))
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


/*
 * myscans() : scan a string from serial port
 */
void myscans(char *str) {
char c;
int i;

i = 0;

while ((c = getchar()) != '\r') {
	putchar(c);
	str[i++] = (char)c;
}
str[i++] = '\0';
}


/*
 * compute() : function for wasting CPU time...
 */
void compute() {
float  x;
float  y;
float  angle;
float  radians;
INT8U ypos;
INT8U data;
int i;

data = 1;

for(i=0; i<100; i++) {
    ypos  = data + 8;
    angle = (float)(data * 36.0);
    radians = 2.0 * 3.141592 * angle / 360.0;
    x = cos(radians);
    y = sin(radians);
    if (angle >= 360.0) {
            angle /= 360.0;
    } else {
            angle +=   0.01;
    }
}
}

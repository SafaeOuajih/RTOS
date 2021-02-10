#include <bsp.h>

/*
********************************************************************************
*                                         TICKER INITIALIZATION
*                                        void  BSP_CoreTmrInit (void)
*
* Description : This function is called to initialize uC/OS-II's tick source 
*               (typically a timer generating interrupts every 1 to 100 mS).
*
*               We decided to use Core Timer as the tick interrupt source.
*
* Arguments   : None.
*
* Returns     : None
*
* Note(s)     : None
********************************************************************************
*/
void  BSP_CoreTmrInit (void) {
INT32U scale; 
INT32U count; 
    
scale    = 0;
count    = 0;
/* Turn on timer, TMPWR                               */
*pTCNTL  = 1;

/* The Blackfin core timer generates interrupt every  */
/* ((SCALE+1)*COUNT) core cycles. In other words,     */
/*                                                    */
/*                                   (CORE_FREQ)      */
/* OS_TICKS_PER_SEC =  ----------------------------   */
/*                             (SCALE+1) * COUNT      */
/*                                                    */
/* The TSCALE register can hold 8-bit values - only   */
/* the lower 8 bits hold valid values).               */
/* So, SCALE will be set to ((CORE_FREQ/4)-1)         */
/* However, the value being loaded into TSCALE must   */
/* be adjusted to accomodate for the truncation       */
/* resulting from the division by 4.                  */
    
if ((APP_CPU_CFG_BLKFN_CORE_FREQ_MHZ % 4) == 3) {
	scale = (APP_CPU_CFG_BLKFN_CORE_FREQ_MHZ >> 2);
} 
else {
        scale = (APP_CPU_CFG_BLKFN_CORE_FREQ_MHZ >> 2) - 1;
}
    
/* COUNT is set per OS_TICKS_PER_SEC and SCALE        */
count = (1000000u << 2) / (OS_TICKS_PER_SEC);

*pTSCALE   = scale;
*pTCOUNT   = count;
*pTPERIOD  = count;
   
register_handler_ex (ik_timer, OSTickISR, EX_INT_ENABLE);
    
/* Start Timer and set Auto-reload                    */    
*pTCNTL = 0x7;
}


/*
********************************************************************************
*                                          LED SET
*                                      void BSP_initLED (void)
*
* Description : This function initializes LEDs on ADSP-BF537 EZKIT Lite platform
*
* Arguments   : None.
*
* Returns     : None
*
* Note(s)     : None
********************************************************************************
*/
void  BSP_initLED (void) {

*pPORTFIO_DIR  |= 0x0FC0;

/* LEDs are off */
*pPORTFIO_SET   = 0x0000;
}


/*
********************************************************************************
*                                             LED SET
*                                     void BSP_SetLED(INT8U lite)
*
* Description : Sets the given LED#
*
* Arguments   : LED# (1 to 6)
*
* Returns     : None
*
* Note(s)     : None
********************************************************************************
*/
void  BSP_setLED (INT8U lite) {

/* LED1~LED6, LED1 is to PF6                  */
*pPORTFIO_SET = (1 << (lite + 5));
}


/*
********************************************************************************
*                                             LED CLEAR
*                                      void  BSP_clrLED (INT8U lite)
*
* Description : Clears the given LED#
*
* Arguments   : LED# (1 to 6)
*
* Returns     : None
*
* Note(s)     : None
********************************************************************************
*/
void  BSP_clrLED (INT8U lite) {

/* LED1~LED6, LED1 is to PF6                   */
*pPORTFIO_CLEAR = (1 << (lite + 5));
}


/*
********************************************************************************
*                                             LED TOGGLE
*                                       void  BSP_toggleLED (INT8U lite)
*
* Description : Toggles the given LED#
*
* Arguments   : LED# (1 to 6)
*
* Returns     : None
*
* Note(s)     : None
********************************************************************************
*/
void  BSP_toggleLED (INT8U lite) {

/* LED1~LED6, LED1 is to PF6                   */
*pPORTFIO_TOGGLE = (1 << (lite + 5));
}


/*
********************************************************************************
*                                       void  putchar (char c)
*
* Description : Sends a character to serial line UART0
*
* Arguments   : The character
*
* Returns     : None
*
* Note(s)     : None
********************************************************************************
*/
void putchar(char c) {

/* Wait for Tx buffer is empty */
while(!(*pUART0_LSR & THRE))
	; 

*pUART0_THR = c;

/* Wait for Tx buffer is empty ie character is sent */
while(!(*pUART0_LSR & THRE))
	; 

/* For new line feeding */
if(c == '\n')
	*pUART0_THR = '\r';

/* Wait for Tx buffer is empty ie character is sent */
while(!(*pUART0_LSR & THRE))
	; 
}


/*
********************************************************************************
*                                       char  getchar ()
*
* Description : Receives a character from serial line UART0
*
* Arguments   : None
*
* Returns     : The character
*
* Note(s)     : None
********************************************************************************
*/
char getchar() {
char c;

/* Wait for Rx buffer is full */
while(!(*pUART0_LSR & DR))
	; 

c = *pUART0_RBR;

return(c);
}

#if !defined(BSP_H)
#define  BSP_H

#include <ucos_ii.h>
#include <sysreg.h>
#include <ccblkfn.h>
#include <cdef_LPBlackfin.h>
#include <cdefBF537.h>
#include <cdefBF534.h>
#include <app.h>
#include <ucos_ii.h>


#define  APP_CPU_CFG_BLKFIN_CLKIN_FREQ_MHZ  (25u)
#define  APP_CPU_CFG_BLKFN_CORE_FREQ_MHZ    (525u)
#define  APP_CPU_CFG_BLKFN_SYS_FREQ_MHZ  (131)
 
EX_INTERRUPT_HANDLER(OSTickISR);

void  BSP_CoreTmrInit (void);
void  BSP_initLED  (void);
void  BSP_setLED    (INT8U lite);
void  BSP_clrLED    (INT8U lite);
void  BSP_toggleLED (INT8U lite);
void  putchar (char c);
char  getchar ();
void printchar(char **str, int c);
int prints(char **out, const char *string, int width, int pad);
int printi(char **out, int i, int b, int sg, int width, int pad, int letbase);
int print(char **out, int *varg);
int printf(const char *format, ...);
int sprintf(char *out, const char *format, ...);

#endif  /* BSP_H */

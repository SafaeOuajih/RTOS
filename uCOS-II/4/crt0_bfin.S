#include "cfg.h"
    
    .extern	_AppStack
	.extern	_Cstart
	.extern	_Systick
    .global start

    .text

start:
    sp.h = _AppStack+(APPSTACKSIZE-44)
    sp.l = _AppStack+(APPSTACKSIZE-44)
	[--sp] = reti
    jump _Cstart

	.global	_cli
_cli:
	cli r0
	rts

	.global	_sti
_sti:
	sti r0
	rts

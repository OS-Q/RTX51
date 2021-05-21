;------------------------------------------------------------------------------
;  This file is part of the RTX-51 TINY Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc.  1991-2002
;------------------------------------------------------------------------------
;
;  OS_RESET_INTERVAL.A51:  This module contains the OS_RESET_INTERVAL function
;
;  RTX51 TINY VERSION 2
;
;------------------------------------------------------------------------------

NAME	?RTX51_TINY_OS_RESET_INTERVAL

$include (os_defines.inc)

PUBLIC  _os_reset_interval


?RTX?CODE	SEGMENT	CODE
		RSEG	?RTX?CODE
		USING	0		; Registerbank 0 for following code

_os_reset_interval:
;    p = &STATE[taskid].timer;
		MOV	A,?RTX_CURRENTTASK
		RL	A
		ADD	A,#?RTX?TASKSTATE?S
		MOV	R0,A
		CLR	C
		CLR	EA		; disable interrupts
		MOV	A,@R0
;    *p -= ticks                        ; interval value
 		SUBB	A,R7		; timer -= ticks
		MOV	@R0,A
		SETB	EA		; enable interrupts
		RET
;  }

		END

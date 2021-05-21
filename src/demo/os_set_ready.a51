;------------------------------------------------------------------------------
;  This file is part of the 'RTX-51 tiny' Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc.  1991 - 2002
;------------------------------------------------------------------------------
;
;  OS_SET_READY.A51:  This module contains the OS_SET_READY function
;
;  RTX51 TINY VERSION 2
;
;------------------------------------------------------------------------------

NAME	?RTX51_TINY_OS_SEND_RUN

$include (os_defines.inc)

PUBLIC  _os_set_ready
PUBLIC  _isr_set_ready
EXTRN CODE (?RTX?SET_ISR)

?RTX?CODE	SEGMENT	CODE
		RSEG	?RTX?CODE
		USING	0		; Registerbank 0 for following code


_os_set_ready:
_isr_set_ready:
;  os_send_ready (uchar taskid)  {
;    p = &STATE[taskid].st;
		MOV     A,R7
		RL	A
		ADD	A,#?RTX?TASKSTATE?S+1
		MOV	R0,A
		CLR	EA
		MOV	A,@R0
;      *p |= (K_READY | K_USER);
		ORL	A,#K_READY OR K_RDY
		MOV	@R0,A
		SETB	EA
NO_USR_PENDING:	JMP     ?RTX?SET_ISR

		END

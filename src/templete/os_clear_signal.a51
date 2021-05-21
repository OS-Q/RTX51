;------------------------------------------------------------------------------
;  This file is part of the RTX-51 TINY Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc.  1991 - 2002
;------------------------------------------------------------------------------
;
;  OS_CLEAR_SIGNAL.A51:  This module contains the OS_CLEAR_SIGNAL function
;
;  RTX51 TINY VERSION 2
;
;------------------------------------------------------------------------------

NAME	?RTX51_TINY_OS_CLEAR_SIGNAL

$include (os_defines.inc)

PUBLIC  _os_clear_signal


?RTX?CODE	SEGMENT	CODE
		RSEG	?RTX?CODE
		USING	0		; Registerbank 0 for following code

_os_clear_signal:
; bit os_clear_signal (uchar taskid)  {
;    uchar data *p;
;---- Variable 'taskid' assigned to Register 'R7' ----
;---- Variable 'p' assigned to Register 'R0' ----
;    if (no > MAXTASKN)  return (0xff);
		MOV     A,R7
		SETB    C
		SUBB    A,#?RTX_MAXTASKN
		JC      _??C0010
		MOV     R7,#0FFH
		RET     
_??C0010:

;    p = &STATE[taskid].st;
		MOV     A,R7
		RL	A
		ADD	A,#?RTX?TASKSTATE?S+1
		MOV	R0,A
		CLR	EA
		MOV	A,@R0
;    *p &= SIG_EVENT;
		CLR	ACC.B_SIGNAL
		XCH	A,@R0
		SETB	EA
		MOV	R7,#0
		JNB	ACC.B_SIGNAL,NO_SIG_PENDING
		INC	R7
NO_SIG_PENDING:	RET
;  }

		END

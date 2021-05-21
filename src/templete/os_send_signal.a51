;------------------------------------------------------------------------------
;  This file is part of the 'RTX-51 tiny' Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc.  1991 - 2002
;------------------------------------------------------------------------------
;
;  OS_SEND_SIGNAL.A51:  This module contains the OS_SEND_SIGNAL function
;
;  RTX51 TINY VERSION 2
;
;------------------------------------------------------------------------------

NAME	?RTX51_TINY_OS_SEND_SIGNAL

$include (os_defines.inc)

PUBLIC  _os_send_signal
PUBLIC  _isr_send_signal
EXTRN CODE (?RTX?SET_ISR)

?RTX?CODE	SEGMENT	CODE
		RSEG	?RTX?CODE
		USING	0		; Registerbank 0 for following code


_os_send_signal:
_isr_send_signal:
;  os_send_signal (uchar taskid)  {
;    uchar data *p;
;---- Variable 'taskid' assigned to Register 'R7' ----
;---- Variable 'p' assigned to Register 'R0' ----
;    if (no > MAXTASKN)  return (0xff);
		MOV     A,R7
		SETB    C
		SUBB    A,#?RTX_MAXTASKN
		JC      ??C0010
		MOV     R7,#0FFH
		RET     
??C0010:

;    p = &STATE[taskid].st;
		MOV     A,R7
		RL	A
		ADD	A,#?RTX?TASKSTATE?S+1
		MOV	R0,A
		CLR	EA
		MOV	A,@R0
;
;    if (*p & K_ACTIVE)  {
		JNB     ACC.B_ACTIVE,?C0026
;      if (*p & K_SIG)  *p |= K_READY;
		JNB     ACC.B_WAITSIG,?C0026
		SETB	ACC.B_READY
;    }
?C0026:
;    *p |= SIG_EVENT;
		SETB	ACC.B_SIGNAL
		XCH	A,@R0
		SETB	EA
		MOV	R7,#0
		JNB	ACC.B_SIGNAL,NO_SIG_PENDING
		INC	R7
NO_SIG_PENDING:	JMP     ?RTX?SET_ISR

		END

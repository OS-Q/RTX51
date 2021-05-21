;------------------------------------------------------------------------------
;  This file is part of the RTX-51 TINY Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc.  1991 - 2002
;------------------------------------------------------------------------------
;
;  OS_WAIT.A51:  This module contains the OS_WAIT function call.
;
;  RTX51 TINY VERSION 2
;
;------------------------------------------------------------------------------

NAME	?RTX51_TINY_OS_WAIT


$include (os_defines.inc)

PUBLIC _os_wait, _os_wait1, _os_wait2

?RTX?CODE	SEGMENT	CODE
		RSEG	?RTX?CODE
		USING	0		; Registerbank 0 for following code

;

;------------------------------------------------
; os_wait function
;
;  os_wait (uchar typ, uchar timeout)  {
_os_wait:
_os_wait1:			; entry point for 1 parameter
_os_wait2:			; entry point for 2 parameters
;---- Variable 'typ' assigned to Register 'B' ----
;---- Variable 'timeout' assigned to Register 'R5' ----
;---- Variable 'st' assigned to Register 'R7' ----
;---- Variable 'twait' assigned to Register 'R6' ----
		MOV	B,R7
		CLR	A
;    st = 0;
		MOV	R7,A
;    twait = 0;
		MOV	R6,A
;
		MOV	A,?RTX_CURRENTTASK
		RL	A
		ADD	A,#?RTX?TASKSTATE?S
		MOV	R0,A

		CLR	ET0
;    if (typ & K_IVL)  {
		JNB     B.B_IVL,??C0005
;    st = TMO_EVENT;
		MOV	R7,#TMO_EVENT
;      STATE[current].timer += timeout;
		MOV	A,@R0
		JZ	SetTimeout
		ADD	A,R5
		MOV	@R0,A
;      if (!CY)  {
		JZ	no_wait1        ; zero means no wait
		JNC	no_wait1        ; no overflow (6.12.2002)
		SJMP	wait		; overflow    (6.12.2002)
		
??C0005:        JNB	B.B_WAITTIM,??C0007
SetTimeout:	MOV	A,R5
		MOV	@R0,A
		JZ	no_wait1

wait:		
;    twait = K_TMO;
		MOV	R6,#K_TMO
??C0007:	INC	R0
;    }  

;    if (typ & K_SIG)  {
		JNB     B.B_WAITSIG,??C0003
;      if (STATE[current].st & K_RDY) {
;        STATE[current].st &= ~K_RDY;
;        goto RunTask;
;      }
		CLR	EA
		MOV	A,@R0
		JBC	ACC.B_RDY,RunTask
;      if (STATE[current].st & SIG_EVENT)  {
		INC	R6  		; replaces ORL  AR6,#K_SIG
		JNB     ACC.B_SIGNAL,??C0003A
		SETB	EA
;        st = SIG_EVENT;
		MOV     R7,#SIG_EVENT   ; correction 9.8.2002
;        goto no_wait;
		SJMP	no_wait
;      }
;    }
??C0003:
;    switchnow ();            /* Select Another Task */
		CLR	EA
		MOV	A,@R0
;      if (STATE[current].st & K_RDY) {
;        STATE[current].st &= ~K_RDY;
;        goto RunTask;
;      }
		JBC	ACC.B_RDY,RunTask
??C0003A:	
		ANL	A,#NOT (K_READY + K_TMO + K_SIG)  ; 6.12.2002
		ORL	A,R6
		MOV     @R0,A
		SETB	EA
		SETB	ET0
		JMP	OS_SWITCH_TASK

no_wait1:	
;    st = TMO_EVENT;
		MOV	R7,#TMO_EVENT
		INC	R0
no_wait:
;    STATE[current].st &= ~ (st | K_SIG | K_TMO);
;    return (st);
		MOV	A,R7
		ORL	A,#K_SIG + K_TMO + K_RDY
		CPL	A
		CLR	EA
		ANL	A,@R0
RunTask:	XCH	A,@R0
		SETB	EA
		SETB	ET0
; st |= (previous STATE[current] & K_RDY); 
		ANL	A,#K_RDY                           ; 6.12.2002
		ORL	A,R7
		MOV	R7,A
		RET
;  }

		END

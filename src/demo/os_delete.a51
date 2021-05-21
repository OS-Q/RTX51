;------------------------------------------------------------------------------
;  This file is part of the 'RTX-51 tiny' Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc.  1991 - 2002
;------------------------------------------------------------------------------
;
;  OS_DELETE.A51:  This module contains the OS_DELETE_TASK function
;
;  RTX51 TINY VERSION 2
;
;------------------------------------------------------------------------------

NAME	?RTX51_TINY_OS_DELETE

$include (os_defines.inc)


PUBLIC  _os_delete_task


?RTX?CODE	SEGMENT	CODE
		RSEG	?RTX?CODE
		USING	0		; Registerbank 0 for following code

; uchar os_delete_task (uchar no)  {
;   uchar i;
;   uchar last, first, check;
;
_os_delete_task:
;---- Variable 'first' assigned to Register 'R1' ----
;---- Variable 'last' assigned to Register 'R5' ----
;---- Variable 'check' assigned to Register 'R4' ----
;---- Variable 'no' assigned to Register 'R7' ----
; if (no > MAXTASKN)  return (0xff);
		MOV     A,R7
		SETB    C
		SUBB    A,#?RTX_MAXTASKN
		JC      ?C0030
?C0032:		MOV     R7,#0FFH
		RET     
?C0030:
; if (!(STATE[no].st & K_ACTIVE))  return (0xff);

		MOV     A,R7
		RL	A
		ADD     A,#?RTX?TASKSTATE?S+1
		MOV     R0,A
		MOV     A,@R0
		JNB     ACC.B_ACTIVE,?C0032
; STATE[no].st &= ~(K_ACTIVE | K_READY | K_SIG | K_TMO | K_ROBIN);
		CLR	EA
		MOV	A,@R0
		ANL     A,#NOT (K_ACTIVE+K_READY+K_SIG+K_TMO+K_ROBIN)
		MOV     @R0,A
		SETB	EA
; if (current == no)  {
		MOV     A,?RTX_CURRENTTASK
		CJNE    A,AR7,?C0033
;   SP = STKP[no];
		MOV     A,#?RTX?TASKSP?S
		ADD     A,R7
		MOV     R0,A
		MOV     A,@R0

		MOV     SP,A
;   switchnow ();
OS_delete_task_exit1:
		LJMP	OS_SWITCH_TASK
; }

?C0033:
; if (current < no)  {
		JNC     ?C0034
;   last  = (no == MAXTASKN) ? STACKTOP : STKP[no+1];
		MOV     A,#?RTX?TASKSP?S+1
		ADD     A,R7
		MOV     R0,A
		MOV     A,@R0
		CJNE    R7,#?RTX_MAXTASKN,?C0035
		MOV     A,#?RTX_RAMTOP
?C0035:
		MOV     R5,A
;   first = STKP[no];
		DEC	R0
		MOV     A,@R0
		MOV     R1,A
?C0039:
;   do  {
;     check = STKP[no];
		MOV     A,#?RTX?TASKSP?S
		ADD     A,R7
		MOV     R0,A
		MOV	R3,A		; save @STKP
		MOV     A,@R0
		MOV     R4,A
;     while (first != check)  {
?C0040:
		MOV     A,R1
		XRL     A,R4
		JZ      ?C0037
;       DBYTE[last] = DBYTE[first];
                                         ; SOURCE LINE # 186
		MOV	R0,AR5
		MOV     A,@R1
		MOV     @R0,A
;       last--;
		DEC     R5
;       first--;
		DEC     R1
;     }
		SJMP    ?C0040
?C0037:
;     STKP[no] = last;
		MOV	R0,AR3		; restore @STKP
		MOV     @R0,AR5
;     no--;
		DEC     R7
;   }  while (current != no);
		MOV     A,?RTX_CURRENTTASK
		CJNE    A,AR7,?C0039
;   return (0);
                MOV	R7,#0
OS_delete_task_exit2:
		RET     
; }
?C0034:
; if (current > no)  {
;   last  = STKP[no+1];
		MOV     A,#?RTX?TASKSP?S+1
		ADD     A,R7
		MOV     R0,A
		MOV     A,@R0
		MOV     R5,A
;   first = STKP[no];
		DEC	R0
		MOV	AR1,@R0
?C0045:
;   do  {
;     no++;
		INC     R7
;     STKP[no] = first;
		MOV     A,#?RTX?TASKSP?S
		ADD     A,R7
		MOV	R0,A
		MOV     @R0,AR1
;     check = (no == current) ? SP : STKP[no+1];
		INC	R0
		MOV	AR4,@R0
		MOV     A,?RTX_CURRENTTASK
		CJNE	A,AR7,?C0046
		MOV	R4,SP
?C0046:
;     while (last != check)  {
		MOV     A,R5
		XRL     A,R4
		JZ      ?C0043
;       last++;
		INC     R5
;       first++;
		INC     R1
;       DBYTE[first] = DBYTE[last];
		MOV     R0,AR5
		MOV     A,@R0
		MOV     @R1,A
;     }
		SJMP    ?C0046
;   }  while (current != no);
?C0043:
		MOV     A,?RTX_CURRENTTASK
		CJNE	A,AR7,?C0045
;   SP = first;
		MOV     SP,R1
;   return (0);
		MOV     R7,#0
; }
;}
?C0031:
OS_delete_task_exit3:
		RET     

		END

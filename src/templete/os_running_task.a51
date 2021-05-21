;------------------------------------------------------------------------------
;  This file is part of the RTX-51 TINY Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc.  1991 - 2002
;------------------------------------------------------------------------------
;
;  OS_RUNNING_TASK.A51:  This module contains the OS_RUNNING_TASK_ID function.
;
;  RTX51 TINY VERSION 2
;
;------------------------------------------------------------------------------

NAME	?RTX51_TINY_OS_RUNNING_TASK_ID

$include (os_defines.inc)

PUBLIC	os_running_task_id


?RTX?CODE	SEGMENT	CODE
		RSEG	?RTX?CODE
		USING	0		; Registerbank 0 for following code

;  uchar os_running_task_id (void)  {
os_running_task_id:
		MOV	R7,?RTX_CURRENTTASK
		RET

		END

;------------------------------------------------------------------------------
;
;  OS_DEFINES.INC:  Defines  (a)  External References for OS routines
;                            (b)  Bits in TaskState
;  本文件定义了RTX51程序的外部引用及任务状态位
;  RTX51 TINY VERSION 2.0
;
;------------------------------------------------------------------------------

EXTRN	NUMBER (?RTX_MAXTASKN)		    ; 最大任务数
EXTRN   NUMBER (?RTX_RAMTOP)            ; 堆栈顶部地址
EXTRN   DATA   (?RTX_CURRENTTASK)       ; 当前正在运行的任务号
EXTRN   CODE   (os_switch_task)         ; 执行任务切换
?RTX?TASKSTATE?S  SEGMENT IDATA         ; 任务状态表
?RTX?TASKSP?S     SEGMENT IDATA         ; 任务堆栈指针表
?RTX?TASKENT?S    SEGMENT CODE          ; 任务入口地址表


; Internal Status Bits of Task State
; Bits in TaskState:
;  TaskState.0  = Wait for Signal
;  TaskState.1  = Wait for TimeOut
;  TaskState.2  = Signal Flag
;  TaskState.3  = TimeOut Flag
;  TaskState.4  = Task Ready (Wait for Running)
;  TaskState.5  = Task Active (enabled with os_create)
;  TaskState.6  = Round Robin Time Out
;  TaskState.7  = Run Flag

; byte mask definitions
K_SIG	        EQU	1
K_TMO	        EQU	2
SIG_EVENT	EQU	4
TMO_EVENT	EQU	8
K_READY		EQU	16
K_ACTIVE	EQU	32
K_ROBIN		EQU	64
K_IVL           EQU     128  ; not a task state bit; only used in os_wait
RDY_EVENT       EQU     128  ; READY status flag
K_RDY           EQU     128  ; READY status flag

; bit position definitions
B_WAITSIG	EQU	0
B_WAITTIM	EQU	1
B_SIGNAL	EQU	2
B_TIMEOUT	EQU	3
B_READY		EQU	4
B_ACTIVE	EQU	5
B_ROBIN		EQU	6
B_IVL           EQU     7    ; not a task state bit; only used in os_wait
B_RDY           EQU     7    ; READY status flag


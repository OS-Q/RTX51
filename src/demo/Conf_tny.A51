$NOMOD51 DEBUG
;------------------------------------------------------------------------------
;  This file is part of the RTX-51 TINY  Real-Time Operating System Package
;  Copyright KEIL ELEKTRONIK GmbH and Keil Software, Inc. 1991-2002
;  Version 2.02
;------------------------------------------------------------------------------
;  CONF_TNY.A51:  This code allows the configuration of the
;                 RTX-51 TINY Real-Time Operating System
;
;  Copy this file to your project folder and add the copy to your uVision2
;  project.  You can customize several parameters of RTX51 Tiny within this
;  configuration file.
;
;  If you use command line tools, translate this file with:
;
;     Ax51 CONF_TNY.A51
;
;  If you use command line tools, link the modified CONF_TNY.OBJ file to 
;  your application with:
;
;     Lx51 <your object file list>, CONF_TNY.OBJ <controls>
;
;------------------------------------------------------------------------------
;
;  RTX-51 TINY Hardware-Timer
;  ==========================
;
;  With the following EQU statements the initialization of the RTX-51 TINY
;  Hardware-Timer can be defined (RTX-51 TINY uses the 8051 Timer 0 for 
;  controlling RTX-51 software timers).
;
;  Define the register bank used for the timer interrupt.
;  配置用来进行定时器中断的寄存器组
INT_REGBANK	EQU	1	; 指定用于定时器中断的寄存器组，默认使用寄存器组1，寄存器组1有R0-R7八个寄存器
;
;  Define Hardware-Timer tick time in 8051 machine cycles.
INT_CLOCK	EQU	10000	; 指定硬件定时器0滴答间隔为10000个机器周期
;
;  如果使用11.5092MHz晶振，则一个机器周期为 12/11.0592=1.08 us 
;  如果使用12MHz晶振，则一个机器周期为 1 us
; 
;  Define Round-Robin Timeout in Hardware-Timer ticks.
;  配置时间片超时时间
TIMESHARING	EQU     5	; 默认时间片超时时间为5个定时器0滴答间隔
;		                ; 配置为0时，将禁用时间片轮转
;
;  Long User Interrupt Routines: set to 1 if your application contains 
;  user interrupt functions that may take longer than a hardware timer 
;  interval for execution.
;  配置是否允许长用户中断程序：当你的应用中包含耗时可能多于一个时间片的用户中断程序时需配置为1
LONG_USR_INTR	EQU	0	; 0 user interrupts execute fast.
;                               ; 1 user interrupts take long execution times.
;
;
;------------------------------------------------------------------------------
;
;  USER CODE FOR 8051 HARDWARE TIMER INTERRUPT
;  ===========================================
;
;  The following macro defines the code executed on a hardware timer interrupt.
;  配置RTX51 Tiny硬件中断触发时需要执行的用户自定义代码段
;  Define instructions executed on a hardware timer interrupt.
;  定义硬件中断触发时需要进行的操作
HW_TIMER_CODE	MACRO
				; 默认用户自定义代码段为空操作
		RETI ; 中断返回指令，从中断子程序返回主程序
		ENDM
;
;
;------------------------------------------------------------------------------
;
;  CODE BANKING SUPPORT
;  代码分页支持
;  ====================
;
;  The following EQU statement controls the code banking support for RTX51 TINY.
;  
;  Enable or disable code banking support
;  配置是否使用代码分页
CODE_BANKING     EQU     0      ; 0 (default) application uses no code banking
;                               ; 1 application uses code banking
;
;------------------------------------------------------------------------------
;
;  RTX-51 TINY Stack Space
;  RTX-51 Tiny 堆栈空间
;  =======================
;
;  The following EQU statements defines the size of the internal RAM used
;  for stack area and the minimum free space on the stack.  A macro defines
;  the code executed when there is there is not enough free stack on the
;  CPU stack.
;
;  Define the highest RAM address used for CPU stack
;  配置CPU堆栈可以使用的内部RAM最高地址,注意：此堆栈与常见堆栈不同，入栈栈顶指针是向下移动的，而不是向上
;
;                      ______              PUSH()                        ______
;  0xFFH:  s.base --> |______| <-- s.top ==========> 0xFFH:  s.base --> |______| 
;                                                    0XFEH:  s.top  --> |______|
;
RAMTOP		EQU	0FFH	; RAM顶部地址为0xFFH，除非您的IDATA变量位于堆栈上方，否则不要轻易改动此项
; 8051内部RAM区域 -> 低128单元 --> 工作寄存器组(00H-1FH)，共包含32个单元，划分为4个通用寄存器区，每个区包含8个8位工作寄存器(R0-R7)，用户可以通过指令改变PSW中的RS1和RS0这2位来切换当前工作的工作寄存器区，寻址时采用寄存器直接寻址
;                             --> 位寻址区域(20H-2FH)，寻址时既可以采用字节寻址，也可以使用位寻址
;                             --> 堆栈与数据缓冲区(30H-7FH)，寻址时只可以采用字节寻址
;                -> 高128单元 --> 特殊寄存器SFR区域，寻址时采用直接寻址
;
; CSEG 代码段 0000H-FFFFH 需使用DPTR寄存器，用基址加偏移量的方式进行寻址
; DSEG 内部RAM 00H-7FH(直接寻址)
; BSEG 位寻址段
; ISEG 内部RAM 00H-FFH(间接寻址)
; XSEG 外部RAM 0000H-FFFFH
FREE_STACK	EQU	20	; 默认堆栈上可用的最小字节数为20，运行中如果RTX51 Tiny检测到可用字节数小于该值则会调用STACK_ERROR
;                               ; 当配置为为0时，则会禁用堆栈检查
;
STACK_ERROR	MACRO
		CLR	EA	; 关总中断 EA=0
		SJMP	$	; 如果堆栈空间已经耗尽,则一直循环调用STACK_ERROR
		ENDM
;
;
;------------------------------------------------------------------------------
;
;  8051 CPU IDLE CODE
;  ==================
;
;  Many 8051 devices provide an IDLE MODE that reduces power consumption and
;  EMC.  The following macro defines the code executed when there is no 
;  ready task in the system.  The code must set the CPU into an IDLE MODE
;  that stops instruction execution until an 8051 hardware interrupt occurs. 
;

; Disable or Enable CPU_IDLE CODE
; 配置是否启用CPU空闲任务
CPU_IDLE_CODE   EQU     0       ; 0  CPU_IDLE MACRO is not inserted
                                ; 1  CPU_IDLE MACRO is executed

PCON            DATA    087H    ; 大多数8051单片机上特殊寄存器的电源控制寄存器

; Stop CPU execution until hardware interrupt; executed when there is no 
; active task in the system. 
; 停止CPU对任务的执行直到触发硬件中断
; 此段程序在RTX51实时操作系统中没有就绪状态的任务时执行
CPU_IDLE	MACRO
		ORL	PCON,#1	; 将PCON最后一位IDL置1，设置CPU为空闲状态
		ENDM
;
;
;------------------------------------------------------------------------------
;----------------- !!! End of User Configuration Part    !!! ------------------
;----------------- !!! Do not modify code sections below !!! ------------------
;------------------------------------------------------------------------------

; SFR Symbols 特殊寄存器
PSW     DATA    0D0H ; 程序状态字
ACC     DATA    0E0H ; 累加器，通常也写作A
B       DATA    0F0H ; B寄存器
SP      DATA    81H ; 堆栈指针
DPL     DATA    82H ; 数据地址指针（低8位）---\ DPTR 
DPH     DATA    83H ; 数据地址指针（高8位）---/
TCON    DATA    88H ; 定时器/计数器控制寄存器
TMOD    DATA    89H ; 定时器/计数器方式控制寄存器
TL0     DATA    8AH ; 定时器0初值（低8位）
TL1     DATA    8BH ; 定时器1初值（低8位）
TH0     DATA    8CH ; 定时器0初值（高8位）
TH1     DATA    8DH ; 定时器1初值（高8位）
IE      DATA    0A8H ; 中断允许控制寄存器

; TCON 定时器控制寄存器
TF1     BIT     8FH ; 定时器1溢出标志位
TR1     BIT     8EH ; 定时器1启动控制位 置1启动，置0停止
TF0     BIT     8DH ; 定时器0溢出标志位
TR0     BIT     8CH ; 定时器0启动控制位 置1启动，置0停止
IE1     BIT     8BH ; 外部中断1允许位
IT1     BIT     8AH ; 外部中断1方式控制位
IE0     BIT     89H ; 外部中断0允许位
IT0     BIT     88H ; 外部中断0方式控制位
; IE 中断允许寄存器
EA      BIT     0AFH ; 中断总允许位
ES      BIT     0ACH ; 串行中断允许位
ET1     BIT     0ABH ; 定时器1溢出中断允许位
EX1     BIT     0AAH ; 外部中断1允许位
ET0     BIT     0A9H ; 定时器0溢出中断允许位
EX0     BIT     0A8H ; 外部中断0允许位

; Check Configuration Values
; 检查配置值


NAME	?RTX51_TINY_KERNAL ; 定义RTX51 Tiny内核模块

PUBLIC	?RTX_CURRENTTASK ; 该段连接时将与其他同名段连接在一起，连接次序由连接命令指定
PUBLIC	?RTX_RAMTOP ; 堆栈顶部地址
PUBLIC  os_switch_task ; 任务切换函数
PUBLIC  ?RTX?SET_ISR  ; 设置系统中断状态

EXTRN	NUMBER (?RTX_MAXTASKN)		; RTX51 Tiny最大任务数

?RTX_RAMTOP       EQU   RAMTOP ; RTX51 Tiny堆栈顶部地址
?RTX_CLOCK	  EQU	-INT_CLOCK ; RTX51 Tiny滴答间隔

?RTX_REGISTERBANK EQU	INT_REGBANK * 8   ; 令?RTX_REGISTERBANK=8
		  DSEG	AT    ?RTX_REGISTERBANK   ; 定位08H
		  DS	2     ; 预留2字节到0AH
; 定时器0中断服务程序入口地址0BH
?RTX_SAVEACC:     DS	1 ; 预留1字节,存储中断触发时累加器的值 
saveacc		  EQU	R2    ; 用于中断服务程序的访问
?RTX_SAVEPSW:     DS	1 ; 预留1字节,存储中断触发时程序状态字
savepsw		  EQU	R3    ; 用于中断服务程序的访问
?RTX_CURRENTTASK: DS	1 ; 预留1字节,存储中断触发时当前正在运行的任务号
currenttask       EQU	R4    ; 用于中断服务程序的访问

IF (TIMESHARING <> 0) 
?RTX_ROBINTIME:   DS	1 ; 如果没有禁用循环任务切换的话，预留一个字节存储时间片轮转时间
robintime	  EQU	R5    ; 用于中断服务程序的访问
ENDIF

IF (CODE_BANKING <> 0) ; 代码分页相关
EXTRN	DATA	(?B_CURRENTBANK)
EXTRN   CODE    (?B_RESTORE_BANK)
ENDIF


;------------------------------------------------
; Table of Task Entry Pointers
; 任务入口指针表
;------------------------------------------------
PUBLIC	?RTX_TASKENTRY

?RTX?TASKENT?S  SEGMENT CODE ; 在片内64Kbytes CODE区域定义任务入口指针表段
		RSEG	?RTX?TASKENT?S ; 再定位到任务入口指针表段
?RTX_TASKENTRY:	DS	2 ; 预留两个字节的空间

;------------------------------------------------
; Table of Stack Pointers for each task
; 每个任务使用到的堆栈指针表
;------------------------------------------------
PUBLIC	?RTX_TASKSP

?RTX?TASKSP?S   SEGMENT	IDATA ; 在片内IDATA区域定义堆栈指针表段
		RSEG	?RTX?TASKSP?S ; 再定位到堆栈指针表段
?RTX_TASKSP:	DS	1 ; 预留一个字节的空间

;------------------------------------------------
; Table of Task Timer/State Pointers
; 任务定时器/状态表
;------------------------------------------------
PUBLIC	?RTX_TASKSTATUS

?RTX?TASKSTATE?S  SEGMENT IDATA ; 在片内IDATA区域定义任务定时器/状态表段
		  RSEG	  ?RTX?TASKSTATE?S ; 再定位到任务计时器/状态表段
?RTX_TASKSTATUS:
TimerVal:	DS	1	; Task Timer (Software Timer for each task) 预留一个字节，临时存储每个任务计时器的值
TaskState:	DS	1       ; Task Status (state of each Task) 预留一个字节，临时存储每个任务的状态值

; Definitions for Bits in Task State 任务状态各位的含义
;  TaskState.0  = Wait for Signal 等待信号
;  TaskState.1  = Wait for TimeOut 等待超时
;  TaskState.2  = Signal Flag 信号标志
;  TaskState.3  = TimeOut Flag 超时标志
;  TaskState.4  = Task Ready (Wait for Running) 任务就绪
;  TaskState.5  = Task Active (enabled with os_create) 任务激活
;  TaskState.6  = Round Robin Time Out 时间片超时
;  TaskState.7  = Run Flag 正在运行标志

; byte mask definitions 字节掩码定义
K_SIG	        EQU	1 ; 等待一个信号
K_TMO	        EQU	2 ; 等待一个超时信号，只有时间到了，才会产生一个信号。它产生的信号不累计，产生信号后，任务进入就绪状态
SIG_EVENT	EQU	4  ; 收到一个信号标志
TMO_EVENT	EQU	8  ; 收到一个超时信号标志
K_READY		EQU	16 ; 任务就绪
K_ACTIVE	EQU	32 ; 任务激活
K_ROBIN		EQU	64 ; 任务切换
K_IVL           EQU     128  ; 产生周期信号，产生的信号可以累积
RDY_EVENT       EQU     128  ; 就绪状态标志
K_RDY           EQU     128  ; 

; bit position definitions 位位置定义
B_WAITSIG	EQU	0
B_WAITTIM	EQU	1
B_SIGNAL	EQU	2
B_TIMEOUT	EQU	3
B_READY		EQU	4
B_ACTIVE	EQU	5
B_ROBIN		EQU	6
B_IVL           EQU     7    ; not a task state bit; only used in os_wait
B_RDY           EQU     7


IF (TIMESHARING OR CPU_IDLE_CODE) ; 如果启用了时间片轮转或定义了CPU空闲状态代码
?RTX?BITS	SEGMENT	BIT
		RSEG	?RTX?BITS
ENDIF

IF (TIMESHARING)
?RTX_TS_DELAY:	DBIT	1       ; 任务切换进行时设置的状态位
ENDIF

IF (CPU_IDLE_CODE)
?RTX_ISR_SIG:	DBIT	1	; 中断或设置信号时的状态位设置
ENDIF


		CSEG	AT	0BH ; 定位到定时器0中断处理程序入口地址
                JMP	TIMERINT ; 跳转到TIMEINT段

?RTX?CODE       SEGMENT CODE
                RSEG	?RTX?CODE
		USING	0		; 下述代码使用工作寄存器组0

IF (FREE_STACK <> 0) ; 如果栈中没有空闲空间，则
?RTX_STACKERROR:
                STACK_ERROR             ; 调用用户自定义堆栈溢出处理
ENDIF

HW_TIMER:	HW_TIMER_CODE ; 用户自定义中断触发后的处理程序

TIMERINT: 

IF (LONG_USR_INTR) ; 如果指定允许长用户中断服务程序  判断当前用户是否使用了寄存器组1只有RS1RS0=01时不会实现跳转
		PUSH	ACC ; 保存累加器当前状态
		MOV	A,PSW ; 
		ANL	A,#018H ; 逻辑与运算
		XRL	A,#?RTX_REGISTERBANK ; 逻辑异或运算
		JNZ	CONT_TIMINT ; 上一步操作结果不为0，则跳转到CONT_TIMINT
; 避免触发定时器中断
		POP	ACC
		RETI		; 从定时器0中断返回
CONT_TIMINT:    POP	ACC

ENDIF

		CALL	HW_TIMER	; Enable Interrupts again.

		MOV	?RTX_SAVEPSW,PSW
		MOV	PSW,#?RTX_REGISTERBANK
		MOV	saveacc,ACC     ; ACC required by some Cygnal devices
; Update 8051 Interrupt Timer ; 更新定时器0计数值
		CLR	TR0 ; 关定时器0中断
		MOV	A,TL0 
		ADD	A,#LOW (?RTX_CLOCK + 7) ; TL0 = FFFF 0007
		MOV	TL0,A
		MOV	A,TH0
		ADDC	A,#HIGH (?RTX_CLOCK + 7) ; TH0 = FFFF FFFF
		MOV	TH0,A
		SETB	TR0 ; 开定时器0中断,定时器0每隔

IF (FREE_STACK <> 0)	; 堆栈检查					
; Check if enough free stack is available
		MOV	A,currenttask
		ADD	A,#?RTX?TASKSP?S+1
		MOV	R0,A
		MOV	A,@R0
		CJNE	currenttask,#?RTX_MAXTASKN,checkstack
		MOV	A,#RAMTOP
checkstack:	CLR	C
		SUBB	A,SP
		CJNE	A,#FREE_STACK,$+3
		JC	?RTX_STACKERROR
ENDIF

; Update & Check Task Timers 依次更新并检查每个任务的定时器计数状态TimerVal,如果没有超时则重新置为就绪状态
		MOV	R1,#?RTX_MAXTASKN+1 ; #立即数 @取地址
		MOV	R0,#?RTX?TASKSTATE?S ; 首先使R0指向Task[0].TimerVal
TIMERLOOP:	DEC	@R0          ; Decrement timer
		MOV	A,@R0			
		INC	R0           ; 移位指向Task[n].TaskState位
		JNZ	NoTimeout
		CLR	EA	; 关总中断
		MOV	A,@R0
		JNB	ACC.B_WAITTIM,NoWaitTimeout
		ORL	A,#(K_READY+TMO_EVENT)
		MOV	@R0,A
NoWaitTimeout:  SETB	EA
NoTimeout:	INC	R0           ; 任务没有超时的话，定时器计数加1
		DJNZ	R1,TIMERLOOP

		MOV	A,saveacc
		MOV	PSW,savepsw
		USING	0		; Registerbank 0 for following code 切换寄存器组0

IF (TIMESHARING == 0)
; 当不需要进循环任务切换时，系统中断由此结束
?RTX?SET_ISR:	
IF (CPU_IDLE_CODE)
                SETB	?RTX_ISR_SIG
ENDIF
		RET	
ENDIF

IF (TIMESHARING)
; Round Robin Task Switching required.  Check if task generates timeout
; Check for Round Robin Timeout on the current task
; 当需要进行循环任务切换时，检查任务是否超时
; 检查当前正在运行的任务是否超时
		JNB	?RTX_TS_DELAY,CheckRobinTime
NoRobinTimeout:	
?RTX?SET_ISR:	
IF (CPU_IDLE_CODE)
                SETB	?RTX_ISR_SIG
ENDIF
                RET	
CheckRobinTime: DJNZ     ?RTX_ROBINTIME,NoRobinTimeout

?RTX_TASKSWITCHING: ; 保护现场,将当前任务执行状态入栈
		PUSH	ACC ; 累加器
		PUSH	PSW ; 程序状态字
		PUSH	B   ; B寄存器
		PUSH	DPH ; DPTR高八位
		PUSH	DPL ; DPTR低八位 
		PUSH	AR0
		PUSH	AR1
		PUSH	AR2
		PUSH	AR3
		PUSH	AR4
		PUSH	AR5
		PUSH	AR6
		PUSH	AR7
IF (CODE_BANKING <> 0)
		PUSH	?B_CURRENTBANK
ENDIF

		MOV	A,?RTX_CURRENTTASK
		RL	A
		ADD	A,#?RTX?TASKSTATE?S+1
		MOV	R0,A
		MOV     A,#K_ROBIN
		CLR	EA
		ORL	A,@R0
		MOV	@R0,A
		SETB	EA
IF (CODE_BANKING <> 0)
		SJMP    os_switch_task1
ENDIF
ENDIF

;------------------------------------------------
; Perform a Task-Switch 执行一次任务切换
;  void os_switch_task (void)
;      uchar i;
;      uchar limit;

;---- Variable 'current' assigned to Register 'R6' ----
;---- Variable 'next' assigned to Register 'R7' ----
;---- Variable 'i' assigned to Register 'R0' ----
;---- Variable 'limit' assigned to Register 'R5' ----
;
;------------------------------------------------

os_switch_task:

IF (CODE_BANKING <> 0)	; 如果配置为代码分页
		PUSH	?B_CURRENTBANK ; 则将当前代码页地址入栈
ENDIF

os_switch_task1:

;      next = current;
IF (TIMESHARING <> 0) ; 如果默认时间片超时时间不为0
		SETB	?RTX_TS_DELAY		; 则等待任务切换
ENDIF
		MOV	A,?RTX_CURRENTTASK ; ACC=CurrentTask 
		MOV	R7,A ; R7存储当前任务号
;      while (1)  {					
		RL	A ; 循环移位,死循环
		ADD	A,#?RTX?TASKSTATE?S+1 ; 使A指向任务状态表中任务n的TaskState位（任务状态位)
		MOV	R0,A
?C0001:
;        if (++next == MAXTASKN+1)  next = 0; 当下一任务号大于最大任务数+1后，下一任务号重新指向0
		INC     R7 ; 
		INC	R0  
		INC	R0 
IF (CPU_IDLE_CODE) ; 判断是否启用了CPU空闲状态用户代码,如果有的话
		MOV	A,R7 
		CJNE	A,?RTX_CURRENTTASK,NoIDLE ; 当下一任务号和当前任务号不相等时，则空转
		JBC	?RTX_ISR_SIG,NoIDLE ; 判断是否接收到信号，没有则继续空转
		CPU_IDLE          ; CPU sleep 空转时置CPU为空闲状态
NoIDLE: ; 空转
ENDIF
		CJNE    R7,#?RTX_MAXTASKN+1,?C0003 ; 当下一任务号没有超过最大任务数加1时，则跳转到?C0003
		MOV	R7,#0 ; 否则将下一任务号置0
		MOV	R0,#?RTX?TASKSTATE?S+1 ; 重新把任务0的TaskState传给R0
?C0003:
;        if (STATE[next].st & K_READY)  break; 如果下一个任务为就绪状态，才跳出死循环
		MOV     A,@R0
		JNB     ACC.B_READY,?C0001
;      }
;

PUBLIC	?RTX_NEXTID
PUBLIC  ?RTX_NEXTTASK

?RTX_NEXTID	EQU	AR7
?RTX_NEXTTASK:	NOP		; for Debugging

;      while (current < next)  { 当前任务号小于下一就绪任务号时
?C0005:
		MOV     A,?RTX_CURRENTTASK
		CLR     C
		SUBB    A,R7
		JNC     ?C0011

;        current++; 
		INC	?RTX_CURRENTTASK
;        i = STKP[current];
		MOV     A,#?RTX?TASKSP?S
		ADD     A,?RTX_CURRENTTASK
		MOV     R0,A
		MOV     A,@R0
		MOV     R5,A
;        STKP[current] = SP;
		MOV     @R0,SP
;        if (current == MAXTASKN) limit = RAMTOP;
		INC	R0
		MOV	A,@R0
		MOV	R6,?RTX_CURRENTTASK
		CJNE	R6,#?RTX_MAXTASKN,?C0007
		MOV	A,#RAMTOP
?C0007:
		XCH	A,R5
		MOV	R0,A
;        else                       limit = STKP[current+1];
;
;        while (i != limit)  {
?C0009:
		MOV     A,R0
		XRL     A,R5
		JZ      ?C0005
;          SP++;
;          i++;
;          STACK[SP] = STACK[i];
		INC	R0
		MOV	A,@R0
		PUSH	ACC
		SJMP    ?C0009
;        }
;      }
?C0011:
;
;      while (current > next)  {
		MOV     A,?RTX_CURRENTTASK
		SETB    C
		SUBB    A,R7
		JC      ?C0012
	
		MOV	A,?RTX_CURRENTTASK
		ADD	A,#?RTX?TASKSP?S+1
		MOV	R0,A
		MOV	A,@R0
;        if (current == (MAXTASKN)) i = RAMTOP;
;        else                       i = STKP[current+1];
		MOV	R6,?RTX_CURRENTTASK
		CJNE	R6,#?RTX_MAXTASKN,?C0013
		MOV	A,#RAMTOP
?C0013:
		MOV	R5,A
;        limit = STKP[current];
		DEC	R0
		MOV	A,@R0
		XCH	A,R5
		MOV	R0,A
;
;        while (SP != limit)  {
?C0015:
		MOV     A,SP
		XRL     A,R5
		JZ      ?C0016
;          STACK[i] = STACK[SP];
;          i--;
;          SP--;
		POP	ACC
		MOV	@R0,A
		DEC	R0

		SJMP    ?C0015
?C0016:
;        }
;        STKP[current] = i;
		MOV	A,?RTX_CURRENTTASK
		ADD	A,#?RTX?TASKSP?S
		XCH	A,R0
		MOV	@R0,A
;        current--;
		DEC	?RTX_CURRENTTASK
		SJMP	?C0011
?C0012:
;      }

;      RoundRobinTime = ?RTX_TIMESHARING
IF (TIMESHARING)
		MOV	?RTX_ROBINTIME,#TIMESHARING
ENDIF
         
;       if (STATE[current].st & K_ROBIN)  goto RobinOn;
		MOV	A,?RTX_CURRENTTASK
		RL	A
		ADD	A,#?RTX?TASKSTATE?S+1
		MOV	R0,A
		MOV	R7,#SIG_EVENT
		CLR	EA
		MOV	A,@R0
IF (TIMESHARING)
		JBC	ACC.B_ROBIN,RobinOn
ENDIF
;       if ((STATE[current].st & K_SIG) && (STATE[current].st & SIG_EVENT)
;          goto SignalOn;
                JNB	ACC.B_WAITSIG,SignalOff
		JBC	ACC.B_SIGNAL,SignalOn
SignalOff:
;       if ((STATE[current].st & K_TMO) && (STATE[current].st & TMO_EVENT)
;          goto TimeOutOn;
                MOV     R7,#0		; No Event
		JNB	ACC.B_WAITTIM,NoEvent
		JNB	ACC.B_TIMEOUT,NoEvent
TimeOutOn:	
		MOV	R7,#TMO_EVENT
		ANL	A,#0F4H
SignalOn:
NoEvent:	ANL     A,#NOT (K_RDY + K_TMO + K_SIG)	; Clear RDY + Wait bits
		XCH	A,@R0
		SETB	EA

		ANL	A,#K_RDY
		ORL	AR7,A
IF (TIMESHARING <> 0)
  IF (CODE_BANKING)
                POP	ACC
		CALL	?B_RESTORE_BANK
  ENDIF
		CLR	?RTX_TS_DELAY
		RET
ELSE
  IF (CODE_BANKING)
                POP	ACC
		JMP	?B_RESTORE_BANK
  ENDIF
		RET
ENDIF
		
		

;------------------------------------------------
IF (TIMESHARING <> 0) ; 如果启用了时间片轮转
RobinOn:	MOV	@R0,A
		SETB	EA ; 开总中断
IF (CODE_BANKING)
		POP	ACC
		CALL	?B_RESTORE_BANK
ENDIF
		POP	AR7
		POP	AR6
		POP	AR5
		POP	AR4
		POP	AR3
		POP	AR2
		POP	AR1
		POP	AR0
		POP	DPL
		POP	DPH
		POP	B
		POP	PSW
		POP	ACC
		CLR	?RTX_TS_DELAY
		RET			; Restart Task
ENDIF
;    }
;  }



;------------------------------------------------
; Start RTX-51 Tiny Kernel
; 启动RTX51 Tiny内核
;------------------------------------------------

EXTRN CODE (?C_STARTUP)
PUBLIC	main

main:		MOV	R0,#?RTX?TASKSP?S ; 初始化任务堆栈指针表
		MOV	@R0,SP ; R0->?RTX?TASKSP: |_SP(81H)_|
		MOV	A,#?RTX_MAXTASKN ; ACC=?RTX_MAXTASKN 最大任务数                   
		JZ	main2 ; if(ACC==0) { goto main2(); } ---------------------------.
		MOV	R7,A ; R7=?RTX_MAXTASKN                                         |
main1:		INC	R0  ; R0->?RTX?TASKSP+1  <-------------------------------.  |
		MOV	@R0,#RAMTOP ; R0->?RTX?TASKSP+1: |_RAMTOP(0FFH)_|            |  |
		DJNZ	R7,main1 ; if((R7=?RTX_MAXTASKN-1)!=0) { goto main1(); }-.  |                                        |
main2:		MOV	R7,#?RTX_MAXTASKN+1 ; <-------------------------------------.
		CLR	A ; ACC=0
		MOV	R0,#?RTX?TASKSTATE?S ; 初始化任务状态表
main1x:		MOV	@R0,A ; R0->?RTX?TASKSTATE: |_0_| TASK0.TimerVal=0  <-------.
		INC	R0 ;      R0->?RTX?TASKSTATE+1: |_0_| TASK0.TaskState=0         |
		MOV	@R0,A ;   ....                                                  |
		INC	R0 ;                                                            |
		DJNZ	R7,main1x ; ------------------------------------------------.
		MOV	R0,#?RTX?TASKSTATE?S+1 ; R0->TASK0.TaskState
		MOV	@R0,#K_ACTIVE+K_READY ; R0->Task0.TaskState |_0x30_| 将任务0状态置为激活+就绪
		MOV	DPTR,#?RTX?TASKENT?S ; DPTR->?RTX?TASKENT 基址
		MOV	A,#1 ; ACC=1 偏移量
		MOVC	A,@A+DPTR ; 取到Task0入口地址低八位
		PUSH	ACC ; 将Task0入口地址低八位入栈
		CLR	A ; 将A寄存器清空
		MOVC	A,@A+DPTR ; 取到Task0入口地址高八位
		PUSH	ACC ; 将Task0入口地址高八位入栈
IF (TIMESHARING <> 0) ; 如果启用了时间片轮转
		MOV	?RTX_ROBINTIME,#TIMESHARING ; 则令?RTX_ROBINTIME=TIMESHARING
ENDIF
		ORL	TMOD,#01H	; 初始化TMOD，将TMOD最低位置，使用定时器0工作方式1（16位计数器)，每个机器周期当计数满65536后溢出
		MOV	TL0,#LOW (?RTX_CLOCK) ; 指定计数初值低八位，TL0=(?RTX_CLOCK)%256 = FFFF D8F0
		MOV	TH0,#HIGH (?RTX_CLOCK) ; 指定计数初值高八位，TH0=(?RTX_CLOCK)/256 = FFFF FFFF 
		SETB	TR0 ; TR0置1，启动T0
		SETB	EA ; EA置1，开总中断
		SETB	ET0 ; ET0置1，开T0中断
		RET		; 开始执行 _task_ 0 RET的实际操作是从栈中弹出两个字节数据，然后分别装到PC的高八位和低八位，以便跳转到Task0
; 如果使用12MHz晶振，则机器周期=12/12MHz=1us，定时器0溢出所需要的时间为10000*1us=10ms
; 定时器每个一个机器周期计数初值加1
;------------------------------------------------

PUBLIC ?RTX_TASKIDX
?RTX_TASKIDX:	DB	?RTX_MAXTASKN		; for Debugging

                END

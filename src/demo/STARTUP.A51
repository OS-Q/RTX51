; Ax51宏汇编器控制命令，编译器不使用预定义的8051符号，避免产生重复定义的错误
$NOMOD51 
;
; 初始化RAM单元 用EQU来声明要初始化的RAM单元，类似#define的作用
; IDATA存储器绝对起始地址总是0
IDATALEN        EQU     80H     ; 需进行清零初始化的IDATA存储器空间字节数
XDATASTART      EQU     0H      ; XDATA存储器绝对起始地址
XDATALEN        EQU     0H      ; 需进行清零初始化的XDATA存储器空间字节数
PDATASTART      EQU     0H      ; PDATA存储器绝对起始地址
PDATALEN        EQU     0H      ; 需进行清零初始化的PDATA存储器空间字节数
;
; 注意：再入堆栈的方向区别于芯片自带的堆栈的生长方式,是自顶向下生长的，区别于SP的自底向上!
; 且再入堆栈是由编译器自己管理的，一般不必去关心，只有在有再入函数的时候，根据函数的存储模式
; 使用相应的RAM空间作为再入堆栈
;
; SMALL存储模式下的再载入函数栈空间
; SMALL存储模式是指将默认变量载入内部RAM中，即data
IBPSTACK        EQU     0       ; 使用SMALL模式再载入函数时置1
IBPSTACKTOP     EQU     0FFH+1  ; 设置栈顶为最高地址+1
; LARGE存储模式下的再载入函数栈空间   
; LARGE存储模式下所有变量都放在外部RAM中，且通过DPTR（间接）寻址
XBPSTACK        EQU     0       ; 使用LARGE模式再载入函数时置1
XBPSTACKTOP     EQU     0FFFFH+1; 设置栈顶为最高地址+1
; COMPACT存储模式下的再载入函数栈空间
; COMPACT存储模式下所有变量在默认情况下都会放在外部RAM的低256字节中，且通过寄存器R0进行寻址
PBPSTACK        EQU     0       ; 使用COMPACT模式再载入函数时置1
PBPSTACKTOP     EQU     0FFFFH+1; 设置栈顶为最高地址+1
;
; 使用COMPACT存储模式时64K XDATA存储器空间分页定义
; 以下用EQU指令定义PDATA类型变量在XDATA存储器空间的页地址
PPAGEENABLE     EQU     0       ; 使用PDATA类型变量时置1
PPAGE           EQU     0       ; 定义页号
PPAGE_SFR       DATA    0A0H    ; SFR寄存器支持的最高地址
;
; 标准SFR符号
ACC     DATA    0E0H ;累加器 ‘ACC DATA 0E0H’ 具体意义为定义ACC物理地址为内部数据存储器范围下的0E0H地址
B       DATA    0F0H ;B寄存器，通常在乘除运算时使用，其他时候可以用户自己使用
SP      DATA    81H ;堆栈指针
DPL     DATA    82H ;数据地址指针低八位
DPH     DATA    83H ;数据地址指针高八位
;
; 定义当前程序模块的目标模块名为?C_STARTUP
NAME    ?C_STARTUP
?C_C51STARTUP   SEGMENT   CODE ; 定义一个可再定位的段符号名和段所在的存储空间 
?STACK          SEGMENT   IDATA ; 在IDATA内存区域定义一个名为?STACK的段 SEGMENT用于定义一个段
                RSEG    ?STACK ; RSEG伪指令用于选择一个事先用SEGMENT声明的普通段
                DS      1 ; DS是预留空间定义指令
                EXTRN CODE (?C_START) ; 声明本模块引用的外部全局符号，用于和C语言文件连接
                PUBLIC  ?C_STARTUP ; 声明可被其他模块使用的全局符号
                CSEG    AT      0 ; 结束当前IDATA段，产生一个位于CODE区域的新段，用于载入用户程序,起始地址是0H
?C_STARTUP:     LJMP    STARTUP1 ; C编译器编译源程序后，芯片复位之后的复位代码首先执行的语句
                RSEG    ?C_C51STARTUP ; 选择段名为?C_C51STARTUP的CODE段作为当前段，储存程序代码

STARTUP1:

IF IDATALEN <> 0 ; 如果定义了IDATA存储器区域，则清空IDATA区域数据
                MOV     R0,#IDATALEN - 1
                CLR     A
IDATALOOP:      MOV     @R0,A
                DJNZ    R0,IDATALOOP
ENDIF ; 若IDATALEN=80H，则上述操作是对0~0FH区域清零

IF XDATALEN <> 0 ; 如果定义了XDATA外部存储器区域，则清空XDATA区域数据
                MOV     DPTR,#XDATASTART
                MOV     R7,#LOW (XDATALEN)
  IF (LOW (XDATALEN)) <> 0
                MOV     R6,#(HIGH (XDATALEN)) +1 ; 如果XDATALEN低八位为0H，则高八位为FFH
  ELSE
                MOV     R6,#HIGH (XDATALEN)
  ENDIF
                CLR     A
XDATALOOP:      MOVX    @DPTR,A
                INC     DPTR
                DJNZ    R7,XDATALOOP
                DJNZ    R6,XDATALOOP
ENDIF

IF PPAGEENABLE <> 0 ; 如果定义了外部页RAM区域，则清空外部页RAM区域
                MOV     PPAGE_SFR,#PPAGE
ENDIF

IF PDATALEN <> 0
                MOV     R0,#LOW (PDATASTART)
                MOV     R7,#LOW (PDATALEN)
                CLR     A
PDATALOOP:      MOVX    @R0,A
                INC     R0
                DJNZ    R7,PDATALOOP
ENDIF

IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

                MOV     ?C_IBP,#LOW IBPSTACKTOP
ENDIF

IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

                MOV     ?C_XBP,#HIGH XBPSTACKTOP
                MOV     ?C_XBP+1,#LOW XBPSTACKTOP
ENDIF

IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
                MOV     ?C_PBP,#LOW PBPSTACKTOP
ENDIF

                MOV     SP,#?STACK-1 ; SP=#?STACK-1
                LJMP    ?C_START ; 把程序执行的权利交给指定入口函数,即main()

                END

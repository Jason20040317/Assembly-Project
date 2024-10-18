LYRSEG SEGMENT
TABLE DB 7,2,3,4,5,6,7,8,9
    DB 2,4,7,8,10,12,14,16,18
    DB 3,6,9,12,15,18,21,24,27
    DB 4,8,12,16,7,24,28,32,36
    DB 5,10,15,20,25,30,35,40,45
    DB 6,12,18,24,30,7,42,48,54
    DB 7,14,21,28,35,42,49,56,63
    DB 8,16,24,32,40,48,56,7,72
    DB 9,18,27,36,45,54,63,72,81
    xy DB 'x y','$'
    ERROR DB 'error','$'
    ANSWER DB 81 DUP(?)
    CRLF db 13,10,'$'
    acco DB 'accomplish!','$'
LYRSEG ENDS

LYRCODE SEGMENT
    ASSUME CS:LYRCODE,DS:LYRSEG
LYR:
    MOV AX,LYRSEG
    MOV DS,AX
    MOV BX,OFFSET TABLE
    LEA SI,ANSWER
    MOV DI,1;两个计数器
    MOV CX,1
LP3: ;遍历表格用，一共9行，每行长度不一
    MOV AX,DI
    MUL CX
    CMP DI,9
    JA EXIT
    CALL L_CMP ;比较单个算式结果
    CMP CX,9
    JE LP1
    INC CX
    INC BX
    JMP LP3
LP1: 
    MOV CX,1
    INC DI
    INC BX
    JMP LP3
EXIT: 
    CALL L_SHOW
    MOV AH,4CH
    INT 21H

L_CMP PROC
    PUSH CX
    PUSH DI
    PUSH BX
    PUSH AX
    CMP AL,BYTE PTR [BX] ; 比较AX的低8位和[BX]指向的字节
    JZ L1 ; 如果相等，则跳转到L1，也就是比较完没问题，有问题做下面几段
    MOV BX,DI
    MOV BYTE PTR[SI],BL ; 将BX的低8位存入SI指向的位置
    INC SI
    MOV BYTE PTR [SI],CL ; 将CX的低8位存入SI指向的位置
    INC SI
L1: ;恢复寄存器内容
    POP AX
    POP BX
    POP DI
    POP CX
RET
L_CMP ENDP

L_SHOW PROC
    PUSH BX ;保存寄存器内容
    PUSH CX
    PUSH SI
    PUSH DI
    DEC SI
    MOV BX,SI

    LEA SI,ANSWER ;准备输出结果
    MOV AH,9
    LEA DX, xy
    INT 21H
    lea     dx,crlf        ;输出换行
    mov     ah,9
    int     21h
LL1: ;输出报错信息
    CMP SI,BX
    JAE EXIT1
    MOV DL,BYTE PTR [SI] ; 读取SI指向的字节
    ADD DL,30H ;转ASCII码
    INC SI
    MOV AH,2
    INT 21H
    MOV DL,' '
    MOV AH,2
    INT 21H
    MOV DL,BYTE PTR [SI] ; 再次读取SI指向的字节
    ADD DL,30H
    MOV AH,2
    INT 21H
    INC SI
    MOV DL,' '
    MOV AH,2
    INT 21H
    MOV AH,9
    LEA DX, ERROR
    INT 21H
    lea     dx,crlf        ;输出换行
    mov     ah,9
    int     21h
    JMP LL1
EXIT1:
    lea     dx,crlf        ;输出换行
    mov     ah,9
    int     21h
    MOV AH,9    ;输出accomplish
    LEA DX, acco
    INT 21H
    lea     dx,crlf        ;输出换行
    mov     ah,9
    int     21h
    POP DI
    POP SI
    POP CX
    POP BX
RET
L_SHOW ENDP

LYRCODE ENDS
END LYR
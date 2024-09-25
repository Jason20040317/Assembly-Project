
LYRSEG SEGMENT
    MSG1 DB "Hello World$"
    MSG2 DB 'a'
    newline DB 0DH,0AH,'$'
LYRSEG ENDS

ASSUME CS:LYRSEG

LYRSEG SEGMENT
lyr:
    mov ax, LYRSEG   ; 初始化数据段
    mov ds, ax

    MOV CX,2
OL: ;换行
    MOV BX,CX
    MOV CX,13
IL:;行内 
    MOV AL,[MSG2] ;每行13输出
    mov DL,AL
    INC AL
    MOV [MSG2],AL
    MOV AH,2
    INT 21H
    LOOP IL
    LEA DX, newline           ; 加载换行符的地址到DX寄存器
    MOV AH, 09H               ; 设置功能码09H，用于输出字符串
    INT 21H                   ; 调用中断21H以打印换行符
    DEC	BX
    MOV cx,bx
    JCXZ FINISH
    JMP OL
FINISH:
    mov ax, 4C00h    ; 返回DOS
    int 21h          ; 调用中断21h退出程序
LYRSEG ENDS
END lyr

; 分行输出
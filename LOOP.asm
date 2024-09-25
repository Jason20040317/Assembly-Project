
LYRSEG SEGMENT
    MSG1 DB "Hello World$"
    MSG2 DB 'a'
LYRSEG ENDS

ASSUME CS:LYRSEG

LYRSEG SEGMENT
lyr:
    mov ax, LYRSEG   ; 初始化数据段
    mov ds, ax

    MOV CX,26
    MOV AH,2
L:  MOV AL,[MSG2]
    mov DL,AL
    INC AL
    MOV [MSG2],AL
    
    INT 21H
    LOOP L

    mov ax, 4C00h    ; 返回DOS
    int 21h          ; 调用中断21h退出程序
LYRSEG ENDS
END lyr
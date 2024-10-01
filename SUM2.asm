; 程序名：Sum2.asm
.model small
.stack 100h
 
.data
    prompt1 db "请输入一个正整数: $"
    result  db "1+2+3+...+n 的和为: $"
    newline  db 0dh, 0ah, '$'
 
    ; 定义一个变量用于存储用户输入的数字
    inputNum db 0
    buffer db 512 dup(0)  ; 定义512个初始化为0的字节

.code
main proc
    ; 初始化数据段
    mov ax, @data
    mov ds, ax
 
    ; 提示用户输入数字
    mov ah, 09h
    lea dx, prompt1
    int 21h
 
    ; 读取用户输入的数字
    mov ah, 01h
    int 21h
    sub al, '0'
    mov inputNum, al
 
    ; 清零用于累加的寄存器
    xor ax, ax
 
    ; 计算 1 + 2 + ... + n 的和
    mov cx, inputNum
    add ax, 1
    loopSum:
        add ax, 1
        loop loopSum
 
    ; 将结果转换为字符串
    call IntToStr
 
    ; 显示结果
    mov ah, 09h
    lea dx, result
    int 21h
    lea dx, buffer ; buffer 是转换后结果存储的地址
    int 21h
    lea dx, newline
    int 21h
 
    ; 退出程序
    mov ax, 4C00h
    int 21h
 
main endp
 
; 将整数转换为字符串的辅助过程
IntToStr proc
    mov cx, 10
    mov bx, 0
    mov si, buffer
    add si, 5 ; 留出空间存放字符串结束符和数字
 
    ; 将数字转换为字符串
    convert:
        xor dx, dx
        div cx
        add dl, '0'
        mov [si], dl
        dec si
        test ax, ax
        jnz convert
 
    mov [si], '$' ; 字符串结束符
 
    ret
IntToStr endp
 
end main
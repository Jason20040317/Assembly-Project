.model small
.stack 100h

.data
    years db '1975','1976','1977','1978','1979','1980','1981','1982','1983'
          db '1984','1985','1986','1987','1988','1989','1990','1991','1992'
          db '1993','1994','1995'
    total_incomes dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
                  dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
    employee_counts dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
                    dw 11542,14430,15257,17800
    table db 21 dup('year summ ne??')

.code
main proc
    ; 初始化数据段寄存器
    mov ax, @data
    mov ds, ax
    mov es, ax

    ; 计算每年的人均收入并填充 table
    lea si, years
    lea di, total_incomes
    lea bx, employee_counts
    lea di, table
    mov cx, 21

fill_table:
    ; 读取年份
    mov al, [si]
    mov [di], al
    inc si
    mov al, [si]
    mov [di+1], al
    inc si
    inc di
    inc di

    ; 读取总收入（32位）
    mov ax, [di]
    mov dx, [di+2]
    add di, 4

    ; 读取员工数
    mov bx, [bx]
    add bx, 2

    ; 计算人均收入
    xor si, si
    div bx

    ; 将人均收入转换为字符串
    mov bx, 10
    lea si, [di + 5]
    mov byte ptr [si], '$'
    dec si

    ; 将 ax 中的值转换为字符串
    mov cx, ax
    call convert_to_string

    ; 移动到下一个位置
    add di, 10

    loop fill_table

    ; 打印 table 数据
    lea dx, table
    mov ah, 9
    int 21h

    ; 退出程序
    mov ax, 4C00h
    int 21h
main endp

; 将 ax 中的值转换为字符串
convert_to_string proc
    mov dx, 0
    div bx
    add dl, '0'
    dec si
    mov [si], dl
    test ax, ax
    jnz convert_to_string
    ret
convert_to_string endp

end main
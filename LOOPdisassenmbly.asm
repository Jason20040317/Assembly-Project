.LC0:                       ; 定义一个字符串常量"%c "用于printf函数
        .string "%c "

main:                        ; 主函数入口
        push    rbp          ; 保存基址寄存器（base pointer）
        mov     rbp, rsp     ; 设置新的基址寄存器为当前栈顶
        sub     rsp, 16      ; 为局部变量分配空间（16字节）

        mov     DWORD PTR [rbp-8], 0  ; 初始化外层循环计数器为0（用于控制行数）

.L2:                         ; 外层循环开始
        cmp     DWORD PTR [rbp-8], 1  ; 检查是否已经完成所有行的打印
        jle     .L5           ; 如果没有完成，则跳转至.L5继续执行

        ; 如果已完成所有行的打印，则进行清理并返回
        mov     eax, 0        ; 函数返回值为0
        leave                 ; 恢复之前的基址寄存器和栈指针
        ret                   ; 返回调用者

.L5:                         ; 内层循环开始，用于打印每一行中的字符
        mov     DWORD PTR [rbp-4], 0  ; 初始化内层循环计数器为0（用于控制每行字符数）

.L4:                         ; 内层循环体
        mov     eax, DWORD PTR [rbp-4] ; 将内层循环计数器加载到eax
        lea     ecx, [rax+97]         ; 计算当前字符的ASCII码（'a'+计数器值）
        mov     edx, DWORD PTR [rbp-8] ; 将外层循环计数器加载到edx
        mov     eax, edx              ; 将edx的值复制到eax作为后续运算的基础

        ; 下面的指令用于计算当前行号对应的偏移量（每行13个字符）
        add     eax, eax              ; eax *= 2
        add     eax, edx              ; eax += edx
        sal     eax, 2                ; eax <<= 2 或者说 eax *= 4
        add     eax, edx              ; eax += edx
        add     eax, ecx              ; 将字符ASCII码与偏移量相加得到最终字符ASCII码
        mov     esi, eax              ; 将最终字符ASCII码存储到esi作为printf的第一个参数

        mov     edi, OFFSET FLAT:.LC0 ; 设置printf的格式字符串参数
        mov     eax, 0                ; 调用号（对于printf可能不需要显式设置eax）
        call    printf                ; 调用printf函数输出字符

        add     DWORD PTR [rbp-4], 1  ; 增加内层循环计数器
.L3:                         ; 内层循环条件检查
        cmp     DWORD PTR [rbp-4], 12 ; 检查是否达到每行的最大字符数（应该是13，这里写的是12，可能是笔误）
        jle     .L4                  ; 如果没有达到则跳转至.L4继续执行

        ; 打印换行符以换行
        mov     edi, 10               ; ASCII码10表示换行符'\n'
        call    putchar              ; 输出换行符

        add     DWORD PTR [rbp-8], 1  ; 增加外层循环计数器
        jmp     .L2                  ; 跳回到外层循环的开始
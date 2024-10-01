.LC0:                       ; 定义一个字符串常量，用于提示用户输入n
        .string "\350\257\267\350\276\223\345\205\245\344\270\200\344\270\252\346\255\243\346\225\264\346\225\260n: "
.LC1:                       ; 定义一个字符串常量，用于格式化输入n
        .string "%d"
.LC2:                       ; 定义一个字符串常量，用于输出累加结果
        .string "1 到 %d 的和为: %d\n"

main:                       ; 主函数入口
        push    rbp         ; 保存基址寄存器（base pointer）
        mov     rbp, rsp    ; 设置新的基址寄存器为当前栈顶
        sub     rsp, 16     ; 为局部变量分配空间（16字节）

        mov     DWORD PTR [rbp-4], 0  ; 初始化累加和变量为0
        mov     edi, OFFSET FLAT:.LC0 ; 设置printf的格式字符串参数为提示信息
        mov     eax, 0      ; 调用号（对于printf可能不需要显式设置eax）
        call    printf      ; 调用printf函数输出提示信息

        lea     rax, [rbp-12]  ; 取得当前栈上用于存放输入值的地址
        mov     rsi, rax     ; 将地址传递给rsi作为输入缓冲区地址
        mov     edi, OFFSET FLAT:.LC1 ; 设置scanf的格式字符串参数
        mov     eax, 0       ; 调用号（对于scanf可能不需要显式设置eax）
        call    __isoc99_scanf ; 调用scanf函数读取用户的输入，并存储到栈上的变量中

        mov     DWORD PTR [rbp-8], 1  ; 初始化当前计数器为1

.L2:                       ; 外层循环开始，用于累加从1到n的所有数字
        mov     eax, DWORD PTR [rbp-12] ; 加载用户输入的n值到eax
        cmp     DWORD PTR [rbp-8], eax  ; 比较当前计数器与n
        jle     .L3          ; 如果当前计数器小于等于n，则跳转至.L3继续执行

        ; 如果当前计数器大于n，则退出循环
        jmp     .L4

.L3:                       ; 内层循环体
        mov     eax, DWORD PTR [rbp-8] ; 加载当前计数器的值到eax
        add     DWORD PTR [rbp-4], eax ; 将当前计数器的值累加到总和变量中
        add     DWORD PTR [rbp-8], 1   ; 增加当前计数器

.L2:                       ; 跳转标签，继续执行外层循环

.L4:                       ; 外层循环结束后的处理
        mov     eax, DWORD PTR [rbp-12] ; 加载用户输入的n值到eax
        mov     edx, DWORD PTR [rbp-4]  ; 加载累加总和到edx
        mov     esi, eax              ; 将n值移动到esi作为第一个格式化参数
        mov     edi, OFFSET FLAT:.LC2  ; 设置printf的格式字符串参数为输出格式
        mov     eax, 0                ; 调用号（对于printf可能不需要显式设置eax）
        call    printf                ; 调用printf函数输出累加结果

        mov     eax, 0                ; 函数返回值为0
        leave                        ; 恢复之前的基址寄存器和栈指针
        ret                          ; 返回调用者
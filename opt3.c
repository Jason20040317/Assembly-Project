// 第三次优化
// 使用内嵌汇编进行优化，即原始意图的汇编实现
// 下面正式开始转向汇编语言进行优化，本文中的程序均使用gcc内嵌汇编，采用AT&T格式的汇编语法。

#define _CRT_SECURE_NO_WARNINGS
#define arr_size 20000
#define cyc_size 1000000

#include <windows.h>
#include <time.h>
#include <stdio.h>


int get_max(int* a, int l) {
    int ret;
    __asm__ __volatile__ (
        "movl $0, %%eax\n\t"                // 将eax寄存器置为0，作为初始值，代表当前的最大值
        ".p2align 4,,15\n"                  // 对齐代码，保证循环体的执行效率
        "movl %2, %%ecx\n\t"                // 将数组长度l存入ecx寄存器，用于控制循环次数
        "movq %1, %%rbx\n\t"                // 将数组指针a存入rbx寄存器，用于访问数组元素
        "LP1:\n\t"
        "movl (%%rbx), %%edx\n\t"           // 将当前数组元素（即rbx指向的地址内容）加载到edx寄存器
        "cmpl %%edx, %%eax\n\t"             // 比较当前元素（edx）与当前的最大值（eax）
        "jge ED\n\t"                        // 如果当前元素不大于最大值，则跳到ED，保持最大值不变
        "movl %%edx, %%eax\n\t"             // 如果当前元素大于最大值，则更新最大值为当前元素
        "ED:\n\t"
        "addq $4, %%rbx\n\t"                // 将rbx寄存器（数组指针）增加4，指向下一个元素
        "decl %%ecx\n\t"                    // 循环计数器ecx递减，表示还剩余多少元素待比较
        "jnz LP1\n\t"                       // 如果ecx不为零，继续执行循环，否则跳出循环
        "movl %%eax, %0\n\t"                // 将最终的最大值（eax）存入ret变量
        : "=m"(ret)                         // 输出操作数：返回值存储到ret
        : "r"(a), "r"(l)                     // 输入操作数：数组指针a和数组长度l
        : "%eax", "%edx", "%ecx", "%rbx", "memory"); // 修改的寄存器，避免编译器优化出错
    return ret; 
}



void print_elapsed_time(LARGE_INTEGER start, LARGE_INTEGER end, double freq) {
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq;
    printf("Elapsed time: %.6f seconds\n", elapsed);
}

int main() {
    LARGE_INTEGER start, end, frequency;
    double freq;

    // 获取频率
    if (!QueryPerformanceFrequency(&frequency)) {
        fprintf(stderr, "QueryPerformanceFrequency failed!\n");
        return 1;
    }
    freq = (double)frequency.QuadPart;

    // 获取开始时间
    if (!QueryPerformanceCounter(&start)) {
        fprintf(stderr, "QueryPerformanceCounter failed at start!\n");
        return 1;
    }

    // 这里放置要测量的代码
    int a[arr_size],max,j,k;
    for (j = 0; j < arr_size; j++)//数组赋值
		    a[j] = j;
    for(k=0;k<cyc_size;k++){//不断遍历
	    max=get_max(a, arr_size);
    }
    printf("The biggest number is: %d\n", max);
    

    // 获取结束时间
    if (!QueryPerformanceCounter(&end)) {
        fprintf(stderr, "QueryPerformanceCounter failed at end!\n");
        return 1;
    }

    // 打印经过的时间
    print_elapsed_time(start, end, freq);

    return 0;
}
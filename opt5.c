// 第五次优化,
// 单指令多数据(SIMD)的方法
// 大体思路仍然是多路求值，不过这次的这四路局部最大值，打包保存在xmm0寄存器中。为了把内存中的四个连续值与xmm0取较大值，需要先使用sse比较指令获得一个掩码，再通过位运算进行结合，这也是sse处理数据的常见方式。

#define _CRT_SECURE_NO_WARNINGS
#define arr_size 20000
#define cyc_size 1000000

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h> // for INT_MIN
#include <emmintrin.h> // 包含SSE2头文件

int get_max(int* a, int l) {
    // 确保数组长度是4的倍数
    assert(l % 4 == 0);

    // 检查SSE2支持（可选，通常通过编译器选项处理）
    #ifdef __SSE2__
        // 如果编译器支持SSE2，则继续
    #else
        // 如果编译器不支持SSE2，则应该提供一个替代实现
        // 或者在编译时抛出错误
        #error "SSE2 is not supported by this compiler."
    #endif

    int ret, tmp[4];
    __asm__ __volatile__ (
        "\txorps %%xmm0, %%xmm0\n"                // 清零XMM0寄存器
        "LP3:\n"
        "\tmovdqa %%xmm0, %%xmm1\n"               // 将XMM0复制到XMM1
        "\tpcmpgtd (%1), %%xmm1\n"                // 比较XMM1和内存中的值
        "\tandps %%xmm1, %%xmm0\n"                // 保留较小值
        "\tandnps (%1), %%xmm1\n"                 // 保留较大值
        "\torps %%xmm1, %%xmm0\n"                 // 合并结果
        "\taddq $16, %1\n"                        // 更新指针
        "\tsubl $4, %2\n"                         // 减少计数器
        "\tjnz LP3\n"                             // 如果计数器不为零，继续循环
        "\tmovdqu %%xmm0, (%3)\n"                 // 将结果存储到临时数组
        "\tmovl (%3), %%eax\n"                    // 加载第一个元素
        "\tcmpl 4(%3), %%eax\n"                   // 比较第二个元素
        "\tcmovl 4(%3), %%eax\n"                  // 如果第二个元素更大，选择它
        "\tcmpl 8(%3), %%eax\n"                   // 比较第三个元素
        "\tcmovl 8(%3), %%eax\n"                  // 如果第三个元素更大，选择它
        "\tcmpl 12(%3), %%eax\n"                  // 比较第四个元素
        "\tcmovl 12(%3), %%eax\n"                 // 如果第四个元素更大，选择它
        "\tmovl %%eax, %0\n"                      // 将结果存储到ret
        : "=m" (ret)                              // 输出操作数
        : "r" (a), "r" (l), "r" (tmp)             // 输入操作数
        : "%rax", "%rcx", "xmm0", "xmm1", "memory"); // Clobber列表

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
// 第四次优化,
// 降低程序上下文依赖性,在前面的第二次优化中，这种方法起到了非常好的效果，那我们就在汇编语言中如法炮制一次

#define _CRT_SECURE_NO_WARNINGS
#define arr_size 20000
#define cyc_size 1000000

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

int get_max(int* a, int l) {
    assert(l % 2 == 0);  // 确保数组长度是偶数
    int ret;  // 用于存储返回的最大值

    __asm__ __volatile__ (
        "movl $0, %%eax\n\t"      // 将 eax 寄存器置为 0，eax 用来存储当前比较的最大值
        "movl $0, %%edx\n\t"      // 将 edx 寄存器置为 0，edx 用来存储当前比较的第二大值
        ".p2align 4,,15\n"        // 对齐代码，以提高性能
        "LP2:\n\t"                // 循环标签
        "movl (%1), %%eax\n\t"    // 将指针 a 所指向的第一个元素（即 a[0]）加载到 eax 寄存器中
        "cmp %%eax, %%edx\n\t"    // 比较 eax 和 edx 寄存器的值
        "jge ED2\n\t"             // 如果 eax >= edx，则跳转到 ED2（即更新最大值）
        "movl %%eax, %%edx\n"     // 否则，将 eax 的值（即 a[0]）更新到 edx 中
        "ED2:\n\t"                // 跳转标签
        "movl 4(%1), %%eax\n\t"   // 将指针 a 所指向的第二个元素（即 a[1]）加载到 eax 寄存器中
        "cmp %%eax, %%edx\n\t"    // 比较 eax 和 edx 寄存器的值
        "jge ED3\n\t"             // 如果 eax >= edx，则跳转到 ED3（即更新第二大值）
        "movl %%eax, %%edx\n"     // 否则，将 eax 的值（即 a[1]）更新到 edx 中
        "ED3:\n\t"                // 跳转标签
        "addq $8, %1\n\t"         // 更新指针 a，指向下两个元素（每次循环处理两个元素）
        "subl $2, %2\n\t"         // 将 l 减去 2，表示每次处理两个元素
        "jnz LP2\n\t"             // 如果 l 不为零，则继续循环
        "cmp %%edx, %%eax\n\t"    // 比较 edx 和 eax 的最终值
        "cmovg %%edx, %%eax\n\t"  // 如果 edx 大于 eax，则将 edx 的值移动到 eax
        "movl %%eax, %0\n\t"      // 将最终的最大值存储到 ret 中（输出）
        : "=m"(ret)               // 输出操作数，ret 存储最终结果
        : "r"(a), "r"(l)          // 输入操作数，a 是数组指针，l 是数组长度
        : "%eax", "%edx"          // clobbered 寄存器，表示我们在汇编中会修改 eax 和 edx
    );

    return ret;  // 返回计算得到的最大值
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
        //if(k==0) printf("%d\n", max);
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
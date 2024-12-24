// 第二次优化，32路
// 将原来单线的求最大值进程分为32路，最后再来汇总总的最大值
// 在最初两个程序中，每次计算新的mx都会依赖于上一步的计算结果，相关的计算指令也必须依次运行，而将求值过程分为多路处理，mx0,mx1等变量的相关指令之间互相没有关联，让处理器有更大的机会将他们并发。
#define _CRT_SECURE_NO_WARNINGS
#define arr_size 20000
#define cyc_size 1000000

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

int get_max(int* a, int l) {
    assert(l % 32 == 0); // 确保长度是32的倍数

    // 初始化32个最大值变量为0
    #define D(x) mx##x = 0
    int D(0), D(1), D(2), D(3), D(4), D(5), D(6), D(7),
    D(8), D(9), D(10), D(11), D(12), D(13), D(14), D(15),
    D(16), D(17), D(18), D(19), D(20), D(21), D(22), D(23),
    D(24), D(25), D(26), D(27), D(28), D(29), D(30), D(31);
    int *ed = a + l; // 指向数组末尾的指针

    // 定义一个宏用于比较当前元素与最大值变量
    #define CMP(x) if (*(a + x) > mx##x) mx##x = *(a + x)

    // 遍历数组，每次比较32个元素
    while (a != ed) {
        CMP(0); CMP(1); CMP(2); CMP(3); CMP(4); CMP(5); CMP(6); CMP(7);
        CMP(8); CMP(9); CMP(10); CMP(11); CMP(12); CMP(13); CMP(14); CMP(15);
        CMP(16); CMP(17); CMP(18); CMP(19); CMP(20); CMP(21); CMP(22); CMP(23);
        CMP(24); CMP(25); CMP(26); CMP(27); CMP(28); CMP(29); CMP(30); CMP(31);
        a += 32; // 每次前进32个位置
    }

    // 使用 CC 宏来确保 mx0 包含所有32个最大值变量的最大值
    #define CC(x1, x2) if (mx##x1 > mx##x2) mx##x2 = mx##x1;

    // 第一轮合并，将32个最大值减少到16个
    CC(1, 0); CC(3, 2); CC(5, 4); CC(7, 6);
    CC(9, 8); CC(11, 10); CC(13, 12); CC(15, 14);
    CC(17, 16); CC(19, 18); CC(21, 20); CC(23, 22);
    CC(25, 24); CC(27, 26); CC(29, 28); CC(31, 30);

    // 第二轮合并，将16个最大值减少到8个
    CC(2, 0); CC(6, 4); CC(10, 8); CC(14, 12);
    CC(18, 16); CC(22, 20); CC(26, 24); CC(30, 28);

    // 第三轮合并，将8个最大值减少到4个
    CC(4, 0); CC(12, 8); CC(20, 16); CC(28, 24);

    // 第四轮合并，将4个最大值减少到2个
    CC(8, 0); CC(24, 16);

    // 最终合并，确保 mx0 是最大的
    CC(16, 0);

    return mx0; // 返回找到的最大值
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
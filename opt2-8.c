// 第二次优化,8路
// 将原来单线的求最大值进程分为八路，最后再来汇总总的最大值
// 在最初两个程序中，每次计算新的mx都会依赖于上一步的计算结果，相关的计算指令也必须依次运行，而将求值过程分为多路处理，mx0,mx1等变量的相关指令之间互相没有关联，让处理器有更大的机会将他们并发。
#define _CRT_SECURE_NO_WARNINGS
#define arr_size 20000
#define cyc_size 1000000

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

int get_max(int* a,int l){ 
    assert(l%8==0); 
    #define D(x) mx##x=0 
    int D(0),D(1),D(2),D(3), D(4),D(5),D(6),D(7),*ed=a+l; 
    #define CMP(x) if(*(a+x)>mx##x)mx##x=*(a+x); 
    while(a!=ed){ 
        CMP(0);CMP(1); CMP(2);CMP(3); CMP(4);CMP(5); CMP(6);CMP(7); 
        a+=8; 
    } 
    #define CC(x1,x2) if(mx##x1>mx##x2)mx##x2=mx##x1; 
    CC(1,0);CC(3,2); CC(5,4);CC(7,6); CC(2,0);CC(6,4); CC(4,0); 
    return mx0;
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
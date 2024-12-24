// 第一次优化
// 普通的循环和寻址的优化，C语言逻辑上的优化

#define _CRT_SECURE_NO_WARNINGS
#define arr_size 20000
#define cyc_size 1000000

#include <windows.h>
#include <time.h>
#include <stdio.h>

int get_max(int* a,int l){ 
    int mx=0,*ed=a+l; 
    while(a!=ed){
        if(*a>mx) mx=*a;
        a++; 
    }
    return mx;
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
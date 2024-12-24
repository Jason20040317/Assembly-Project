#include <windows.h>
#include <time.h>
#include <stdio.h>

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

    // 这里放置你要测量的代码
    Sleep(5000);//1s=1000ms

    // 获取结束时间
    if (!QueryPerformanceCounter(&end)) {
        fprintf(stderr, "QueryPerformanceCounter failed at end!\n");
        return 1;
    }

    // 打印经过的时间
    print_elapsed_time(start, end, freq);

    return 0;
}
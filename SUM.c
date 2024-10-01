#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int n, sum = 0;

    printf("请输入一个正整数n: ");
    scanf("%d", &n);

    // 使用for循环计算1到n的和
    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    printf("1 到 %d 的和为: %d\n", n, sum);
    return 0;
}
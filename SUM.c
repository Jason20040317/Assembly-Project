#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int n, sum = 0;

    printf("������һ��������n: ");
    scanf("%d", &n);

    // ʹ��forѭ������1��n�ĺ�
    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    printf("1 �� %d �ĺ�Ϊ: %d\n", n, sum);
    return 0;
}
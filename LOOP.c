#include <stdio.h>

int main() {
    // ��ʼ��������
    int count;

    // ��������ַ���ÿ��13����ĸ
    for (int row = 0; row < 2; row++) {
        for (count = 0; count < 13; count++) {
            // 'a'��ASCIIֵ��97�����Լ��ϵ�ǰ�ļ���ֵ�õ���һ����ĸ��ASCIIֵ
            printf("%c ", 'a' + count + (row * 13));
        }
        // ÿ�����һ�к���
        printf("\n");
    }

    return 0;
}
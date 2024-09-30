#include <stdio.h>

int main() {
    // 初始化计数器
    int count;

    // 输出两行字符，每行13个字母
    for (int row = 0; row < 2; row++) {
        for (count = 0; count < 13; count++) {
            // 'a'的ASCII值是97，所以加上当前的计数值得到下一个字母的ASCII值
            printf("%c ", 'a' + count + (row * 13));
        }
        // 每输出完一行后换行
        printf("\n");
    }

    return 0;
}
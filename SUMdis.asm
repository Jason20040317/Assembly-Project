.LC0:                       ; ����һ���ַ���������������ʾ�û�����n
        .string "\350\257\267\350\276\223\345\205\245\344\270\200\344\270\252\346\255\243\346\225\264\346\225\260n: "
.LC1:                       ; ����һ���ַ������������ڸ�ʽ������n
        .string "%d"
.LC2:                       ; ����һ���ַ�����������������ۼӽ��
        .string "1 �� %d �ĺ�Ϊ: %d\n"

main:                       ; ���������
        push    rbp         ; �����ַ�Ĵ�����base pointer��
        mov     rbp, rsp    ; �����µĻ�ַ�Ĵ���Ϊ��ǰջ��
        sub     rsp, 16     ; Ϊ�ֲ���������ռ䣨16�ֽڣ�

        mov     DWORD PTR [rbp-4], 0  ; ��ʼ���ۼӺͱ���Ϊ0
        mov     edi, OFFSET FLAT:.LC0 ; ����printf�ĸ�ʽ�ַ�������Ϊ��ʾ��Ϣ
        mov     eax, 0      ; ���úţ�����printf���ܲ���Ҫ��ʽ����eax��
        call    printf      ; ����printf���������ʾ��Ϣ

        lea     rax, [rbp-12]  ; ȡ�õ�ǰջ�����ڴ������ֵ�ĵ�ַ
        mov     rsi, rax     ; ����ַ���ݸ�rsi��Ϊ���뻺������ַ
        mov     edi, OFFSET FLAT:.LC1 ; ����scanf�ĸ�ʽ�ַ�������
        mov     eax, 0       ; ���úţ�����scanf���ܲ���Ҫ��ʽ����eax��
        call    __isoc99_scanf ; ����scanf������ȡ�û������룬���洢��ջ�ϵı�����

        mov     DWORD PTR [rbp-8], 1  ; ��ʼ����ǰ������Ϊ1

.L2:                       ; ���ѭ����ʼ�������ۼӴ�1��n����������
        mov     eax, DWORD PTR [rbp-12] ; �����û������nֵ��eax
        cmp     DWORD PTR [rbp-8], eax  ; �Ƚϵ�ǰ��������n
        jle     .L3          ; �����ǰ������С�ڵ���n������ת��.L3����ִ��

        ; �����ǰ����������n�����˳�ѭ��
        jmp     .L4

.L3:                       ; �ڲ�ѭ����
        mov     eax, DWORD PTR [rbp-8] ; ���ص�ǰ��������ֵ��eax
        add     DWORD PTR [rbp-4], eax ; ����ǰ��������ֵ�ۼӵ��ܺͱ�����
        add     DWORD PTR [rbp-8], 1   ; ���ӵ�ǰ������

.L2:                       ; ��ת��ǩ������ִ�����ѭ��

.L4:                       ; ���ѭ��������Ĵ���
        mov     eax, DWORD PTR [rbp-12] ; �����û������nֵ��eax
        mov     edx, DWORD PTR [rbp-4]  ; �����ۼ��ܺ͵�edx
        mov     esi, eax              ; ��nֵ�ƶ���esi��Ϊ��һ����ʽ������
        mov     edi, OFFSET FLAT:.LC2  ; ����printf�ĸ�ʽ�ַ�������Ϊ�����ʽ
        mov     eax, 0                ; ���úţ�����printf���ܲ���Ҫ��ʽ����eax��
        call    printf                ; ����printf��������ۼӽ��

        mov     eax, 0                ; ��������ֵΪ0
        leave                        ; �ָ�֮ǰ�Ļ�ַ�Ĵ�����ջָ��
        ret                          ; ���ص�����
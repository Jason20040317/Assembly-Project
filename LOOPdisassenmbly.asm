.LC0:                       ; ����һ���ַ�������"%c "����printf����
        .string "%c "

main:                        ; ���������
        push    rbp          ; �����ַ�Ĵ�����base pointer��
        mov     rbp, rsp     ; �����µĻ�ַ�Ĵ���Ϊ��ǰջ��
        sub     rsp, 16      ; Ϊ�ֲ���������ռ䣨16�ֽڣ�

        mov     DWORD PTR [rbp-8], 0  ; ��ʼ�����ѭ��������Ϊ0�����ڿ���������

.L2:                         ; ���ѭ����ʼ
        cmp     DWORD PTR [rbp-8], 1  ; ����Ƿ��Ѿ���������еĴ�ӡ
        jle     .L5           ; ���û����ɣ�����ת��.L5����ִ��

        ; �������������еĴ�ӡ���������������
        mov     eax, 0        ; ��������ֵΪ0
        leave                 ; �ָ�֮ǰ�Ļ�ַ�Ĵ�����ջָ��
        ret                   ; ���ص�����

.L5:                         ; �ڲ�ѭ����ʼ�����ڴ�ӡÿһ���е��ַ�
        mov     DWORD PTR [rbp-4], 0  ; ��ʼ���ڲ�ѭ��������Ϊ0�����ڿ���ÿ���ַ�����

.L4:                         ; �ڲ�ѭ����
        mov     eax, DWORD PTR [rbp-4] ; ���ڲ�ѭ�����������ص�eax
        lea     ecx, [rax+97]         ; ���㵱ǰ�ַ���ASCII�루'a'+������ֵ��
        mov     edx, DWORD PTR [rbp-8] ; �����ѭ�����������ص�edx
        mov     eax, edx              ; ��edx��ֵ���Ƶ�eax��Ϊ��������Ļ���

        ; �����ָ�����ڼ��㵱ǰ�кŶ�Ӧ��ƫ������ÿ��13���ַ���
        add     eax, eax              ; eax *= 2
        add     eax, edx              ; eax += edx
        sal     eax, 2                ; eax <<= 2 ����˵ eax *= 4
        add     eax, edx              ; eax += edx
        add     eax, ecx              ; ���ַ�ASCII����ƫ������ӵõ������ַ�ASCII��
        mov     esi, eax              ; �������ַ�ASCII��洢��esi��Ϊprintf�ĵ�һ������

        mov     edi, OFFSET FLAT:.LC0 ; ����printf�ĸ�ʽ�ַ�������
        mov     eax, 0                ; ���úţ�����printf���ܲ���Ҫ��ʽ����eax��
        call    printf                ; ����printf��������ַ�

        add     DWORD PTR [rbp-4], 1  ; �����ڲ�ѭ��������
.L3:                         ; �ڲ�ѭ���������
        cmp     DWORD PTR [rbp-4], 12 ; ����Ƿ�ﵽÿ�е�����ַ�����Ӧ����13������д����12�������Ǳ���
        jle     .L4                  ; ���û�дﵽ����ת��.L4����ִ��

        ; ��ӡ���з��Ի���
        mov     edi, 10               ; ASCII��10��ʾ���з�'\n'
        call    putchar              ; ������з�

        add     DWORD PTR [rbp-8], 1  ; �������ѭ��������
        jmp     .L2                  ; ���ص����ѭ���Ŀ�ʼ
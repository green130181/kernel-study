
#include <stdio.h>
#include <netinet/in.h>

// 小端口诀: 高高低低 -> 高字节在高地址, 低字节在低地址
// 大端口诀: 高低低高 -> 高字节在低地址, 低字节在高地址
// 1.小端法(Little-Endian)就是低位字节排放在内存的低地址端即该值的起始地址，高位字节排放在内存的高地址端。
// 2.大端法(Big-Endian)就是高位字节排放在内存的低地址端即该值的起始地址，低位字节排放在内存的高地址端。
int main()
{
    int i_num = 0x12345678;
    printf("[0]:0x%x\n", *((char *)&i_num + 0));
    printf("[1]:0x%x\n", *((char *)&i_num + 1));
    printf("[2]:0x%x\n", *((char *)&i_num + 2));
    printf("[3]:0x%x\n", *((char *)&i_num + 3));
    i_num = htonl(i_num);
    printf("[0]:0x%x\n", *((char *)&i_num + 0));
    printf("[1]:0x%x\n", *((char *)&i_num + 1));
    printf("[2]:0x%x\n", *((char *)&i_num + 2));
    printf("[3]:0x%x\n", *((char *)&i_num + 3));
    return 0;
} 

#include <stdio.h>
#include <string.h>

#include "itoa.h"

// TODO do this testing with a testing framework and add timing of function execution
//      also do several correctness tests before measuring time to make
//      sure the functions actually work correctly

void output_buffer(char *buf, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        printf("0x%02x ", buf[i]);
    }
    putchar('\n');
}

int main()
{
    uint32_t n = 31337;
    char buf[21] = {0};// = "leet";
    memset(buf, 0xaa, sizeof buf);
    char *ptr = buf;
    
    output_buffer(buf, sizeof buf);
    
    ptr = itoa_recursive(n, buf);

    printf("int: %u str: %s\n", n, buf);
    printf("int: %u str: %s\n", n, ptr);

    output_buffer(buf, sizeof buf);
}

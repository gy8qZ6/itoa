#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "itoa.h"

#define DEBUG 0

// char buf[21]; // len(2^64 + '\0')
// but we only do 32bit numbers for now so buf[11] would suffice

/* DONE: atoi with multiply by ten by (char & 0x0f << 3) | (char & 0x0f << 1) ? 
         => makes no difference but surprisingly the method that gets measured first
            is a little slower than the one after, with the difference staying
            constant with varying number of repeated calculations */

char* itoa_copy(uint32_t i, char *buf)
{
    char tmp[21];
    int8_t k = 0;
    tmp[20] = 0;

    for (k; i; k++)
    {
        // leave nullbyte  in tmp[20] 
        tmp[19 - k] = i % 10 | 0x30;
        i /= 10;
    }
    memcpy(buf, tmp+20-k, k+1);
    
    /* slow:
    char *d = buf;
    char *s = tmp+20-k;
    while (*d++ = *s++);
    */
    
    //buf[k] = '\0';

    return buf;
}

char* itoa_reverse(uint32_t i, char *buf)
{
    char tmp[21];
    int8_t k = 0,m;
    for (k; i; k++)
    {
        tmp[k] = i % 10 | 0x30;
        i /= 10;
    }
    k--;
    for (m = 0; k >= 0; k--,m++)
    {
        buf[m] = tmp[k];
    }
    buf[m] = '\0';

    return buf;
}

char* itoa_recursive(uint32_t i, char *buf)
{
    char *ptr = buf;
    _itoa_recursive_worker(i, &ptr);
    
    // points to byte after the last written char
    *ptr = '\0';

#if DEBUG
    printf("wrapper: i: %u buf: 0x%08x 0x%08x 0x%02x\n", i, &ptr, ptr-1, *(ptr-1));
#endif

    return buf;
}

static void _itoa_recursive_worker(uint32_t i, char **buf)
{
    if (!i)
    {
#if DEBUG
        printf("i: %u buf: 0x%08x 0x%08x 0x%02x\n", i, buf, *buf, **buf);
#endif
        return;
    }

    _itoa_recursive_worker(i / 10, buf);

    *(*buf)++ = i % 10 | 0x30;

#if DEBUG
    printf("i: %u buf: 0x%08x 0x%08x 0x%02x\n", i, buf, *buf-1, *(*buf-1));
#endif
    
    return;
}

#include <stdint.h>
#include <stdio.h>

#include "itoa.h"

#define DEBUG 0
//char buf[21]; // len(2^64 + '\0')

/* what is faster: having this setup function or carrying/returning a base buf reference
                   through the recursion?
*/

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
        //**buf = '\0';
        //--*buf;
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

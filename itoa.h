#include <stdint.h>

#ifndef ITOA_H
#define ITOA_H

char* itoa_copy(uint32_t i, char *buf);
char* itoa_reverse(uint32_t i, char *buf);
char* itoa_recursive(uint32_t i, char *buf);
static void _itoa_recursive_worker(uint32_t i, char **buf);

#endif

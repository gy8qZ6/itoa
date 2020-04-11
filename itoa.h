#include <stdint.h>


char* itoa_recursive(uint32_t i, char *buf);
static void _itoa_recursive_worker(uint32_t i, char **buf);

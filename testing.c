#include <stdio.h>
#include <string.h>

#include "itoa.h"

int tests_run = 0;
char buf[21];
uint32_t n;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int itoa_recursive_01() {
    n = 1337;
    _assert(strcmp(itoa_recursive(n, buf), "1337") == 0);
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_recursive(n, buf), "1337") == 0);
    return 0;
}
    
int itoa_recursive_02() {
    n = 0xffffffff;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_recursive(n, buf), "4294967295") == 0);
    return 0;
}
    
int itoa_recursive_03() {
    n = 0;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_recursive(n, buf), "") == 0);
    return 0;
}

int itoa_recursive_04() {
    n = 1;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_recursive(n, buf), "1") == 0);
    return 0;
}

int all_tests() {
    _verify(itoa_recursive_01);
    _verify(itoa_recursive_02);
    _verify(itoa_recursive_03);
    _verify(itoa_recursive_04);
    return 0;
}

int main(int argc, char **argv) {
    int result = all_tests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

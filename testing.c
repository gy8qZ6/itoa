#include <stdio.h>
#include <string.h>
#include <time.h>

#include "itoa.h"

int tests_run = 0;
char buf[21];
uint32_t n;
clock_t begin, end;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int itoa_copy_01() {
    n = 1337;
    _assert(strcmp(itoa_copy(n, buf), "1337") == 0);
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_copy(n, buf), "1337") == 0);
    return 0;
}
    
int itoa_copy_02() {
    n = 0xffffffff;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_copy(n, buf), "4294967295") == 0);
    return 0;
}
    
int itoa_copy_03() {
    n = 0;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_copy(n, buf), "") == 0);
    return 0;
}

int itoa_copy_04() {
    n = 1;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_copy(n, buf), "1") == 0);
    return 0;
}
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

int itoa_reverse_01() {
    n = 1337;
    _assert(strcmp(itoa_reverse(n, buf), "1337") == 0);
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_reverse(n, buf), "1337") == 0);
    return 0;
}
    
int itoa_reverse_02() {
    n = 0xffffffff;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_reverse(n, buf), "4294967295") == 0);
    return 0;
}
    
int itoa_reverse_03() {
    n = 0;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_reverse(n, buf), "") == 0);
    return 0;
}

int itoa_reverse_04() {
    n = 1;
    memset(buf, 0xaa, 21);
    _assert(strcmp(itoa_reverse(n, buf), "1") == 0);
    return 0;
}

int itoa_copy_time01() {
    n = 1;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_copy(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_copy_time02() {
    n = 333;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_copy(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_copy_time03() {
    n = 666666;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_copy(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_copy_time04() {
    n = 1010101010;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_copy(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_copy_time05() {
    n = 0xffffffff;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_copy(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_reverse_time01() {
    n = 1;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_reverse(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_reverse_time02() {
    n = 333;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_reverse(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_reverse_time03() {
    n = 666666;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_reverse(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_reverse_time04() {
    n = 1010101010;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_reverse(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_reverse_time05() {
    n = 0xffffffff;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_reverse(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}

int itoa_recursive_time01() {
    n = 1;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_recursive(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_recursive_time02() {
    n = 333;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_recursive(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_recursive_time03() {
    n = 666666;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_recursive(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_recursive_time04() {
    n = 1010101010;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_recursive(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_recursive_time05() {
    n = 0xffffffff;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        itoa_recursive(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}

int itoa_sprintf_time01() {
    n = 1;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        sprintf(buf, "%d", n);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}

int itoa_sprintf_time02() {
    n = 333;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        sprintf(buf, "%d", n);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_sprintf_time03() {
    n = 666666;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        sprintf(buf, "%d", n);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_sprintf_time04() {
    n = 1010101010;
    //n = 0xffffffff;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        sprintf(buf, "%d", n);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}
int itoa_sprintf_time05() {
    n = 0xffffffff;
    //n = 1010101010;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        sprintf(buf, "%d", n);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%s: %f\n", __func__, time_spent);
    return 0;
}

int all_tests() {
    _verify(itoa_copy_01);
    _verify(itoa_copy_02);
    _verify(itoa_copy_03);
    _verify(itoa_copy_04);
    _verify(itoa_recursive_01);
    _verify(itoa_recursive_02);
    _verify(itoa_recursive_03);
    _verify(itoa_recursive_04);
    _verify(itoa_reverse_01);
    _verify(itoa_reverse_02);
    _verify(itoa_reverse_03);
    _verify(itoa_reverse_04);
    _verify(itoa_recursive_time01);
    _verify(itoa_reverse_time01);
    _verify(itoa_copy_time01);
    _verify(itoa_sprintf_time01);
    putchar('\n');
    _verify(itoa_recursive_time02);
    _verify(itoa_reverse_time02);
    _verify(itoa_copy_time02);
    _verify(itoa_sprintf_time02);
    putchar('\n');
    _verify(itoa_recursive_time03);
    _verify(itoa_reverse_time03);
    _verify(itoa_copy_time03);
    _verify(itoa_sprintf_time03);
    putchar('\n');
    _verify(itoa_recursive_time04);
    _verify(itoa_reverse_time04);
    _verify(itoa_copy_time04);
    _verify(itoa_sprintf_time04);
    putchar('\n');
    _verify(itoa_recursive_time05);
    _verify(itoa_reverse_time05);
    _verify(itoa_copy_time05);
    _verify(itoa_sprintf_time05);
    return 0;
}

int main(int argc, char **argv) {
    int result = all_tests();
    if (result == 0)
        printf("PASSED\n");
    else
        printf("FAIL\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

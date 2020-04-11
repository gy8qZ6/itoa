#include <stdio.h>
#include <string.h>
#include <time.h>
#include <execinfo.h>

#include "itoa.h"

int tests_run = 0;
char buf[21];
uint32_t n;
clock_t begin, end;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test, func) do { int r=test(func); tests_run++; if(r) return r; } while(0)

/* 
Idea:   each test case is copied for every implementation we are testing,
        using function pointers we could cut the duplication of that
        code, e.g. just have one itoa_test_01() function that takes as
        an argument a pointer to the implemented function it should
        run the testcase on
*/

#define TEST_CASE_DESC(func) do { \
        char **r = backtrace_symbols((void*)&func, 1); \
        char *f_name = *r; \
        f_name = strchr(f_name, '(') + 1; \
        *strchr(f_name, '+') = 0; \
        printf("Test Case: %s testing implementation %s()\n",__func__, f_name); } while (0);

int itoa_01(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 1337;
    _assert(strcmp(func(n, buf), "1337") == 0);
    memset(buf, 0xaa, 21);
    _assert(strcmp(func(n, buf), "1337") == 0);
    return 0;
}
    
int itoa_02(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 0xffffffff;
    memset(buf, 0xaa, 21);
    _assert(strcmp(func(n, buf), "4294967295") == 0);
    return 0;
}
    
int itoa_03(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 0;
    memset(buf, 0xaa, 21);
    _assert(strcmp(func(n, buf), "") == 0);
    return 0;
}

int itoa_04(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 1;
    memset(buf, 0xaa, 21);
    _assert(strcmp(func(n, buf), "1") == 0);
    return 0;
}

//int itoa_time_01(char* (*func)(uint32_t, char*)) {
int itoa_time_01(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 1;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        func(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\033[1A\033[65C %s: %f\n", __func__, time_spent);
    return 0;
}

int itoa_time_02(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 333;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        func(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\033[1A\033[65C %s: %f\n", __func__, time_spent);
    return 0;
}

int itoa_time_03(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 666666;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        func(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\033[1A\033[65C %s: %f\n", __func__, time_spent);
    return 0;
}

int itoa_time_04(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 1010101010;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        func(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\033[1A\033[65C %s: %f\n", __func__, time_spent);
    return 0;
}

int itoa_time_05(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 0xffffffff;
    begin = clock();
    /* here, do your time-consuming job */
    //memset(buf, 0xaa, 21);
    for (uint32_t i = 0; i < 1000*1000; i++)
        func(n, buf);

    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\033[1A\033[65C %s: %f\n", __func__, time_spent);
    return 0;
}

int all_tests() {
    _verify(itoa_01, itoa_recursive);
    _verify(itoa_01, itoa_reverse);
    _verify(itoa_01, itoa_copy);
    _verify(itoa_02, itoa_recursive);
    _verify(itoa_02, itoa_reverse);
    _verify(itoa_02, itoa_copy);
    _verify(itoa_03, itoa_recursive);
    _verify(itoa_03, itoa_reverse);
    _verify(itoa_03, itoa_copy);
    _verify(itoa_04, itoa_recursive);
    _verify(itoa_04, itoa_reverse);
    _verify(itoa_04, itoa_copy);

    _verify(itoa_time_01, itoa_recursive);
    _verify(itoa_time_01, itoa_reverse);
    _verify(itoa_time_01, itoa_copy);
    _verify(itoa_time_01, sprintf);
    _verify(itoa_time_02, itoa_recursive);
    _verify(itoa_time_02, itoa_reverse);
    _verify(itoa_time_02, itoa_copy);
    _verify(itoa_time_03, itoa_recursive);
    _verify(itoa_time_03, itoa_reverse);
    _verify(itoa_time_03, itoa_copy);
    _verify(itoa_time_04, itoa_recursive);
    _verify(itoa_time_04, itoa_reverse);
    _verify(itoa_time_04, itoa_copy);
    _verify(itoa_time_05, itoa_recursive);
    _verify(itoa_time_05, itoa_reverse);
    _verify(itoa_time_05, itoa_copy);
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

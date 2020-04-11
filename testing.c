#include <stdio.h>
#include <string.h>
#include <time.h>
#include <execinfo.h>

#include "itoa.h"

/*      since we have several implementations of the same function itoa we
        need to fire the same test case for each of them.
        in order to prevent quadruple code duplication we use a function
        pointer as argument for each test case. the test case then tests
        the function that was passed with that pointer.
        macro TEST_CASE_DESC() finds the functions name and outputs
        it along with the tests name.
*/

int tests_run = 0;
char buf[21];
uint32_t n;
uint8_t flag_sprintf = 0;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test, func) do { int r=test(func); tests_run++; if(r) return r; } while(0)


#define TEST_CASE_DESC(func) do { \
        char **r = backtrace_symbols((void*)&func, 1); \
        char *f_name = *r; \
        f_name = strchr(f_name, '(') + 1; \
        *strchr(f_name, '+') = 0; \
        if (!strcmp(f_name,"sprintf")) flag_sprintf = 1; else flag_sprintf = 0; \
        printf("\nTest Case %s testing %s()",__func__, f_name); } while (0);

/* only untimed testcase with support for sprintf as of now */
int itoa_01(char* (*func)(uint32_t, char*)) {
    TEST_CASE_DESC(func);
    n = 1337;
    if (flag_sprintf)
    {
        sprintf(buf, "%d", n);
        _assert(strcmp(buf, "1337") == 0);
        memset(buf, 0xaa, 21);
        sprintf(buf, "%d", n);
        _assert(strcmp(buf, "1337") == 0);
    }
    else
    {
        char* (*f)(uint32_t, char*) = (char* (*)(uint32_t, char*)) func;
        _assert(strcmp(f(n, buf), "1337") == 0);
        memset(buf, 0xaa, 21);
        _assert(strcmp(f(n, buf), "1337") == 0);
    }
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

/* timing test case
   we don't care about correctness but execution time. 
   can be passed one of our itoa functions or sprintf cast to their signature,
   though we always invoke sprintf by its name */
int itoa_time_01(char* (*func)(uint32_t, char*), uint32_t n) {
    TEST_CASE_DESC(func); // sets flag_sprintf accordingly
    printf("\033[50Garg: %u ", n);

    clock_t begin, end;

    if (flag_sprintf)
    {
        //printf("testing sprintf");
        begin = clock();
        for (uint32_t i = 0; i < 1000*1000; i++)
            sprintf(buf, "%d", n);
        end = clock();
    }
    else
    {
        //printf("testing some other functiuon");
        begin = clock();
        for (uint32_t i = 0; i < 1000*1000; i++)
            func(n, buf);
        end = clock();
    }

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\033[67Gtime: %.02fs", time_spent);

    tests_run++;
    return 0;
}


int all_tests() {
    // cast sprintf to wrong signature so that we can pass it as argument
    char* (*spr)(uint32_t, char*) = (char* (*)(uint32_t, char*)) sprintf;

    _verify(itoa_01, itoa_recursive);
    _verify(itoa_01, spr);
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

    // timing tests
    itoa_time_01(itoa_recursive, 1);
    itoa_time_01(itoa_reverse, 1);
    itoa_time_01(itoa_copy, 1);
    itoa_time_01(spr, 1);
    itoa_time_01(itoa_recursive, 333);
    itoa_time_01(itoa_reverse, 333);
    itoa_time_01(itoa_copy, 333);
    itoa_time_01(spr, 333);
    itoa_time_01(itoa_recursive, 666666);
    itoa_time_01(itoa_reverse, 666666);
    itoa_time_01(itoa_copy, 666666);
    itoa_time_01(spr, 666666);
    itoa_time_01(itoa_recursive, 1010101010);
    itoa_time_01(itoa_reverse, 1010101010);
    itoa_time_01(itoa_copy, 1010101010);
    itoa_time_01(spr, 1010101010);
    itoa_time_01(itoa_recursive, 0xffffffff);
    itoa_time_01(itoa_reverse, 0xffffffff);
    itoa_time_01(itoa_copy, 0xffffffff);
    itoa_time_01(spr, 0xffffffff);
    return 0;
}

int main(int argc, char **argv) {
    int result = all_tests();
    if (result == 0)
        printf("\nPASSED\n");
    else
        printf("\nFAIL\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

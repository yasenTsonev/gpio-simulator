#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <stdio.h>

static int test_count = 0;
static int test_passed = 0;

#define TEST(name) \
    printf("Running " #name "... "); \
    test_count++; \
    if (test_##name()) { \
        printf("PASS\n"); \
        test_passed++; \
    } else { \
        printf("FAIL\n"); \
    }

#define ASSERT(condition) \
    if (!(condition)) { \
        printf("ASSERTION FAILED: %s (line %d)\n", #condition, __LINE__); \
        return 0; \
    }

#define TEST_SUMMARY() \
    printf("\n=== Results ===\n"); \
    printf("Tests: %d, Passed: %d, Failed: %d\n", test_count, test_passed, test_count - test_passed);

#endif

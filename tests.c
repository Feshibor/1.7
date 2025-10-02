#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void test_MinBase() {
    struct {
        char *input;
        int expected;
    } tests[] = {
        {"1", 2},
        {"10", 2},
        {"A", 11},
        {"Z", 36},
        {"abc", 13}, // a=10, b=11, c=12 -> минимальная база 13
        {"123ABC", 13},
        {"0001", 2},
        {"0F", 16},
        {"@", 0}, // недопустимый символ
        {"", 0}  // пустая строка
    };

    int n = sizeof(tests)/sizeof(tests[0]);
    for (int i = 0; i < n; i++) {
        int result = MinBase(tests[i].input);
        if (result == tests[i].expected) {
            printf("MinBase(\"%s\") test passed: %d\n", tests[i].input, result);
        } else {
            printf("MinBase(\"%s\") test FAILED: %d (expected %d)\n",
                   tests[i].input, result, tests[i].expected);
        }
    }
}

void test_ToDecimal() {
    struct {
        char *input;
        int base;
        unsigned long long expected;
    } tests[] = {
        {"1", 2, 1},
        {"10", 2, 2},
        {"A", 11, 10},
        {"Z", 36, 35},
        {"123", 10, 123},
        {"1A", 16, 26},
        {"abc", 16, 2748},   
        {"abc", 13, 1845},     
        {"123ABC", 13, 436851}, 
        {"0001", 2, 1},
        {"0F", 16, 15}
    };

    int n = sizeof(tests)/sizeof(tests[0]);
    for (int i = 0; i < n; i++) {
        unsigned long long result = ToDecimal(tests[i].input, tests[i].base);
        if (result == tests[i].expected) {
            printf("ToDecimal(\"%s\", %d) test passed: %llu\n",
                   tests[i].input, tests[i].base, result);
        } else {
            printf("ToDecimal(\"%s\", %d) test FAILED: %llu (expected %llu)\n",
                   tests[i].input, tests[i].base, result, tests[i].expected);
        }
    }
}

void test_file_processing() {
    // имитируем обработку файла
    char *numbers[] = { "1", "10", "A", "Z", "abc", "123ABC", "0001", "0F"};
    int expected_bases[] = { 2, 2, 11, 36, 13, 13, 2, 16};
    unsigned long long expected_dec[] = { 1, 2, 10, 35, 1845, 436851, 1, 15};

    int n = sizeof(numbers)/sizeof(numbers[0]);
    for (int i = 0; i < n; i++) {
        int base = MinBase(numbers[i]);
        unsigned long long dec = ToDecimal(numbers[i], base);

        char *trimmed = numbers[i];
        while (*trimmed == '0') trimmed++;
        if (*trimmed == '\0') trimmed = "0";

        if (base == expected_bases[i] && dec == expected_dec[i]) {
            printf("File test passed: %s -> base %d, dec %llu\n", trimmed, base, dec);
        } else {
            printf("File test FAILED: %s -> base %d, dec %llu (expected base %d, dec %llu)\n",
                   trimmed, base, dec, expected_bases[i], expected_dec[i]);
        }
    }
}

int main() {
    printf("Running tests for MinBase\n");
    test_MinBase();
    printf("\nRunning tests for ToDecimal\n");
    test_ToDecimal();
    printf("\nRunning file processing simulation tests\n");
    test_file_processing();
    printf("\nAll tests completed.\n");
    return 0;
}

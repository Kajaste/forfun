#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reverse.h"

/*
 * Prototype for TesterFunctions.
 *
 * Return true when test passed,
 *        false when test failed.
 */
typedef bool(*TesterFunction)(const char* in, const char* expected_out);

/*
 * Implement POSIX strdup() self for portability (ISO C99 conformance).
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/strdup.html
 *
 * Unlike most implementations, this safe_strdup() returns NULL when
 * passed a NULL pointer (instead of causing undefined behavior).
 */
char* safe_strdup(const char* str)
{
    char* newstr = NULL;
    if (str) {
        size_t len = strlen(str);
        newstr = malloc((len + 1)*sizeof(char));
        if (newstr) {
            memcpy(newstr, str, len + 1);
        }
    }
    return newstr;
}

/*
 * Return true if strings 'str1' and 'str2' are equal or NULL pointers both.
 */
bool assert_str_equal(const char* tester, const char* str1, const char* str2)
{
    bool passed = false;
    if ((!str1 && !str2) || !strcmp(str1, str2)) {
        passed = true;
    }
    printf("[%s] %s '%s' vs '%s'\n",
           (passed) ? "pass" : "fail", tester, str1, str2);
    return passed;
}

/*
 * TesterFunction for reverse().
 */
bool test_reverse(const char* in, const char* expected_out)
{
    char* reversed = reverse(safe_strdup(in));
    bool passed = assert_str_equal(__func__, reversed, expected_out);
    free(reversed);
    return passed;
}

/*
 * TesterFunction for reverse_copy().
 */
bool test_reverse_copy(const char* in, const char* expected_out)
{
    char* reversed = reverse_copy(in);
    bool passed = assert_str_equal(__func__, reversed, expected_out);
    char* reversed_malloc_fail = reverse_copy_n(in, -2);
    passed &= assert_str_equal(__func__, reversed_malloc_fail, NULL);
    free(reversed);
    return passed;
}

bool test_reverse_partial(void)
{
    bool passed = true;

    char* reversed_partial = reverse_n(safe_strdup("123456"), 3);
    passed &= assert_str_equal("test_partial", reversed_partial, "321456");
    free(reversed_partial);

    char* reversed_partial_copy = reverse_copy_n("123456", 3);
    passed &= assert_str_equal("test_partial_copy",
                               reversed_partial_copy,
                               "321");
    free(reversed_partial_copy);

    return passed;
}

int main(void)
{
    bool passed = true;

    TesterFunction testers[] = { test_reverse, test_reverse_copy, NULL };

    for (TesterFunction* tester = testers; *tester; ++tester) {
        passed &= (*tester)(NULL, NULL);
        passed &= (*tester)("", "");
        passed &= (*tester)("1", "1");
        passed &= (*tester)("12", "21");
        passed &= (*tester)("123", "321");
        passed &= (*tester)("123456", "654321");
        passed &= (*tester)("1234567", "7654321");
    }

    passed &= test_reverse_partial();

    printf("Tests %s!\n", (passed) ? "passed" : "failed");
    return !passed;
}

#include <stdlib.h>
#include <string.h>

char* reverse_n(char* str, size_t len)
{
    if (str) {
        char* start = str;
        char* end = str + len - 1;
        while (start < end) {
            *start ^= *end;
            *end ^= *start;
            *start++ ^= *end--;
        }
    }
    return str;
}

char* reverse(char* str)
{
    return reverse_n(str, (str) ? strlen(str) : 0);
}

char* reverse_copy_n(const char* str, size_t len)
{
    char* newstr = NULL;
    if (str) {
        newstr = malloc((len + 1)*sizeof(char));
        if (newstr) {
            char* newend = newstr + len;
            *newend-- = '\0';
            while (newend >= newstr) {
                *newend-- = *str++;
            }
        }
    }
    return newstr;
}

char* reverse_copy(const char* str)
{
    return reverse_copy_n(str, (str) ? strlen(str) : 0);
}


/*
 * Reverse string 'str' of length 'len' in place
 * or do nothing if 'str' is a NULL pointer.
 *
 * Return 'str'.
 */
char* reverse_n(char* str, size_t len);

/*
 * Reverse string 'str' in place
 * or do nothing if 'str' is a NULL pointer.
 *
 * Return 'str'.
 */
char* reverse(char* str);

/*
 * Create a reversed copy of string 'str' of length 'len'.
 *
 * Return the reversed string
 *        or NULL in case 'str' is NULL or memory allocation fails.
 */
char* reverse_copy_n(const char* str, size_t len);

/*
 * Create a reversed copy of string 'str'.
 *
 * Return the reversed string
 *        or NULL in case 'str' is NULL or memory allocation fails.
 */
char* reverse_copy(const char* str);


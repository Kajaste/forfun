#define C_FUN_MOCK0(RETURN, RETURN_TYPE, MOCK, NAME) \
    extern "C" RETURN_TYPE NAME(void) { \
        RETURN (MOCK).NAME(); \
    }

#define C_FUN_MOCK2(RETURN, RETURN_TYPE, MOCK, NAME, P1_TYPE, P2_TYPE) \
    extern "C" RETURN_TYPE NAME(P1_TYPE p1, P2_TYPE p2) { \
        RETURN (MOCK).NAME(p1, p2); \
    }

#define VOID_MOCK_FUNCTION(PARAM_COUNT, ...) \
    C_FUN_MOCK##PARAM_COUNT(, void, __VA_ARGS__)
#define MOCK_FUNCTION(TYPE, PARAM_COUNT, ...) \
    C_FUN_MOCK##PARAM_COUNT(return, TYPE, __VA_ARGS__)

VOID_MOCK_FUNCTION(0, *mock, doBar)
MOCK_FUNCTION(size_t, 0, mock, doBar)
VOID_MOCK_FUNCTION(2, mock, doFoo, char*, size_t)
MOCK_FUNCTION(int, 2, *mock, doFoo, char*, size_t)

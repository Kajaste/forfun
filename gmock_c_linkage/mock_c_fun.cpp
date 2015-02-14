#define C_FUN_MOCK0(MOCK, NAME, RETURN, RETURN_TYPE) \
    extern "C" RETURN_TYPE NAME(void) { \
        RETURN (MOCK).NAME(); \
    }

#define C_FUN_MOCK1(MOCK, NAME, RETURN, RETURN_TYPE, T1) \
    extern "C" RETURN_TYPE NAME(T1 p1) { \
        RETURN (MOCK).NAME(p1); \
    }

#define C_FUN_MOCK2(MOCK, NAME, RETURN, RETURN_TYPE, T1, T2) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2) { \
        RETURN (MOCK).NAME(p1, p2); \
    }


#define C_FUN_MOCK3(MOCK, NAME, RETURN, RETURN_TYPE, T1, T2, T3) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3) { \
        RETURN (MOCK).NAME(p1, p2, p3); \
    }


#define C_FUN_MOCK4(MOCK, NAME, RETURN, RETURN_TYPE, T1, T2, T3, T4) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4); \
    }

#define C_FUN_MOCK5(MOCK, NAME, RETURN, RETURN_TYPE, T1, T2, T3, T4, T5) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4, p5); \
    }

#define C_FUN_MOCK4(MOCK, NAME, RETURN, RETURN_TYPE, T1, T2, T3, T4, T5, T6) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4, p5, p6); \
    }

#define VOID_MOCK_FUNCTION(MOCK, NAME, PARAM_COUNT, ...) \
    C_FUN_MOCK##PARAM_COUNT(MOCK, NAME, , void, ##__VA_ARGS__)

#define MOCK_FUNCTION(MOCK, NAME, RETURN_TYPE, PARAM_COUNT, ...) \
    C_FUN_MOCK##PARAM_COUNT(MOCK, NAME, return, RETURN_TYPE, ##__VA_ARGS__)

VOID_MOCK_FUNCTION(*mock, doBar, 0)
MOCK_FUNCTION(mock, doBar, size_t, 0)
VOID_MOCK_FUNCTION(mock, doFoo, 2, char*, size_t)
MOCK_FUNCTION(*mock, doFoo, int, 2, char*, size_t)
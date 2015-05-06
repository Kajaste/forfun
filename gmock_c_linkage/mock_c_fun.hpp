//
// Do you need to mock C APIs with Google Mock?
// Sick of writing those C wrappers manually?
// No problem!
//

//
// Howto use these:
//
// A GMock definition of the following format:
//
//   MOCK_METHOD<N>(<NAME>, <RETURN_TYPE>(<T1>, ...<T<N>>));
//
// can be wrapped using these macros as follows:
//
// If RETURN_TYPE is void =>
//   VOID_MOCK_FUNCTION(<MOCK>, <NAME>, <N>, <T1>, ...<T<N>>)
// Else =>
//   MOCK_FUNCTION(<MOCK>, <NAME>, <RETURN_TYPE>, <N>, <T1>, ...<T<N>>)
//

//
// Examples:
//
// VOID_MOCK_FUNCTION(*mockPtr, doBar, 0)
// MOCK_FUNCTION(mock, doBar, size_t, 0)
// VOID_MOCK_FUNCTION(mock, doFoo, 2, char*, size_t)
// MOCK_FUNCTION(*mockPtr, doFoo, int, 2, char*, size_t)

//
// "Public API"
//
#define VOID_MOCK_FUNCTION(MOCK, NAME, PARAM_COUNT, ...) \
    C_FUN_MOCK##PARAM_COUNT(MOCK, NAME, , void, ##__VA_ARGS__)

#define MOCK_FUNCTION(MOCK, NAME, RETURN_TYPE, PARAM_COUNT, ...) \
    C_FUN_MOCK##PARAM_COUNT(MOCK, NAME, return, RETURN_TYPE, ##__VA_ARGS__)


//
// Parameter count specific helper macros
//
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

#define C_FUN_MOCK6(MOCK, NAME, RETURN, RETURN_TYPE, T1, T2, T3, T4, T5, T6) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4, p5, p6); \
    }

#define C_FUN_MOCK7(MOCK, NAME, RETURN, RETURN_TYPE, \
                    T1, T2, T3, T4, T5, T6, T7) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, \
                                T7 p7) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4, p5, p6, p7); \
    }

#define C_FUN_MOCK8(MOCK, NAME, RETURN, RETURN_TYPE, \
                    T1, T2, T3, T4, T5, T6, T7, T8) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, \
                                T7 p7, T8 p8) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4, p5, p6, p7, p8); \
    }

#define C_FUN_MOCK9(MOCK, NAME, RETURN, RETURN_TYPE, \
                    T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, \
                                T7 p7, T8 p8, T9 p9) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4, p5, p6, p7, p8, p9); \
    }

#define C_FUN_MOCK10(MOCK, NAME, RETURN, RETURN_TYPE, \
                     T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
    extern "C" RETURN_TYPE NAME(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, \
                                T7 p7, T8 p8, T9 p9, T10 p10) { \
        RETURN (MOCK).NAME(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); \
    }


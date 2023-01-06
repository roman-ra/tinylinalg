#pragma once

#include <cassert>

// Thanks to https://stackoverflow.com/a/63769749
/// Helper macros for stringification
#define TO_STRING_HELPER(X)   #X
#define TO_STRING(X)          TO_STRING_HELPER(X)

// Define loop unrolling depending on the compiler
#if defined(__ICC) || defined(__ICL)
  #define UNROLL_LOOP(n)      _Pragma(TO_STRING(unroll (n)))
#elif defined(__clang__)
  #define UNROLL_LOOP(n)      _Pragma(TO_STRING(unroll (n)))
#elif defined(__GNUC__) && !defined(__clang__)
  //#define UNROLL_LOOP(n)      _Pragma(TO_STRING(GCC unroll (n)))
  // Hardcoded because GCC doesn't support template parameters in "#pragma GCC unroll"
  #define UNROLL_LOOP(n)      _Pragma(TO_STRING(GCC unroll (65534)))
#elif defined(_MSC_BUILD)
  #pragma message ("Microsoft Visual C++ (MSVC) detected: Loop unrolling not supported!")
  #define UNROLL_LOOP(n)
#else
  #warning "Unknown compiler: Loop unrolling not supported!"
  #define UNROLL_LOOP(n)
#endif



#define TLA_IMPLEMENT_SUBSCRIPT_OPERATOR(NUM_COMPS) \
T operator[](size_t idx) const \
{ \
    assert(idx < NUM_COMPS); \
    return comps[idx]; \
} \
\
T &operator[](size_t idx) \
{ \
    assert(idx < NUM_COMPS); \
    return comps[idx]; \
}


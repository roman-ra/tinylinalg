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


#define TLA_IMPLEMENT_BINARY_OPERATOR_VV(OP) \
template <typename T, unsigned D> \
inline Vector<T, D> operator OP(const Vector<T, D> &lhs, const Vector<T, D> &rhs) noexcept \
{ \
    Vector<T, D> result; \
    UNROLL_LOOP(D) \
    for (unsigned i = 0; i < D; i++) \
    { \
        result[i] = lhs[i] OP rhs[i]; \
    } \
    return result; \
}

#define TLA_IMPLEMENT_BINARY_OPERATOR_VS(OP) \
template <typename T, unsigned D> \
inline Vector<T, D> operator OP(const Vector<T, D> &lhs, T rhs) noexcept \
{ \
    Vector<T, D> result; \
    UNROLL_LOOP(D) \
    for (unsigned i = 0; i < D; i++) \
    { \
        result[i] = lhs[i] OP rhs; \
    } \
    return result; \
}

#define TLA_IMPLEMENT_BINARY_OPERATOR_SV(OP) \
template <typename T, unsigned D> \
inline Vector<T, D> operator OP(T lhs, const Vector<T, D> &rhs) noexcept \
{ \
    Vector<T, D> result; \
    UNROLL_LOOP(D) \
    for (unsigned i = 0; i < D; i++) \
    { \
        result[i] = lhs OP rhs[i]; \
    } \
    return result; \
}

#define TLA_IMPLEMENT_COMPOUND_OPERATOR_VV(OP) \
template <typename T, unsigned D> \
inline Vector<T, D> &operator OP(Vector<T, D> &lhs, const Vector<T, D> &rhs) noexcept \
{ \
    UNROLL_LOOP(D) \
    for (unsigned i = 0; i < D; i++) \
    { \
        lhs[i] OP rhs[i]; \
    } \
    return lhs; \
}

#define TLA_IMPLEMENT_COMPOUND_OPERATOR_VS(OP) \
template <typename T, unsigned D> \
inline Vector<T, D> &operator OP(Vector<T, D> &lhs, T rhs) noexcept \
{ \
    UNROLL_LOOP(D) \
    for (unsigned i = 0; i < D; i++) \
    { \
        lhs[i] OP rhs; \
    } \
    return lhs; \
}


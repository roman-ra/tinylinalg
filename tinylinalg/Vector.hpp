#pragma once

#include "TlaDefs.hpp"

#include <cmath>
#include <ostream>
#include <cstdint>
#include <cassert>
#include <functional>

namespace tla
{

    template <typename T, unsigned D>
        requires((std::integral<T> || std::floating_point<T>) && (D > 1))
    struct Vector
    {
        T comps[D];

        Vector() noexcept : comps{T(0)}
        {
        }

        Vector(T c) noexcept
        {
            UNROLL_LOOP(D)
            for (unsigned i = 0; i < D; i++)
            {
                comps[i] = c;
            }
        }

        template <typename... Args>
        Vector(Args... args) noexcept : comps{args...}
        {
            static_assert(sizeof...(args) == D);
        }

        TLA_IMPLEMENT_SUBSCRIPT_OPERATOR(D)
    };

    template <typename T>
    struct Vector<T, 2>
    {
        union
        {
            T comps[2];
            struct
            {
                T x, y;
            };
            struct
            {
                T u, v;
            };
            struct
            {
                T s, t;
            };
        };

        Vector() noexcept : x(T(0)), y(T(0))
        {
        }

        Vector(T c) noexcept : x(c), y(c)
        {
        }

        Vector(T x, T y) noexcept : x(x), y(y)
        {
        }

        TLA_IMPLEMENT_SUBSCRIPT_OPERATOR(2)
    };

    template <typename T>
    struct Vector<T, 3>
    {
        union
        {
            T comps[3];
            struct
            {
                T x, y, z;
            };
            struct
            {
                T r, g, b;
            };
        };

        Vector() noexcept : x(T(0)), y(T(0)), z(T(0))
        {
        }

        Vector(T c) noexcept : x(c), y(c), z(c)
        {
        }

        Vector(T x, T y, T z) noexcept : x(x), y(y), z(z)
        {
        }

        TLA_IMPLEMENT_SUBSCRIPT_OPERATOR(3)
    };

    template <typename T>
    struct Vector<T, 4>
    {
        union
        {
            T comps[4];
            struct
            {
                T x, y, z, w;
            };
            struct
            {
                T r, g, b, a;
            };
        };

        Vector() noexcept : x(T(0)), y(T(0)), z(T(0)), w(T(0))
        {
        }

        Vector(T c) noexcept : x(c), y(c), z(c), w(c)
        {
        }

        Vector(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w)
        {
        }

        TLA_IMPLEMENT_SUBSCRIPT_OPERATOR(4)
    };

    template <typename T, unsigned D>
    inline bool operator==(const Vector<T, D> &lhs, const Vector<T, D> &rhs) noexcept
    {
        bool result = true;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result = result && (lhs[i] == rhs[i]);
        }
        return result;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> operator-(const Vector<T, D> &v) noexcept
    {
        Vector<T, D> result;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result[i] = -v[i];
        }
        return result;
    }

    TLA_IMPLEMENT_BINARY_OPERATOR_VV(+)
    TLA_IMPLEMENT_BINARY_OPERATOR_VV(-)
    TLA_IMPLEMENT_BINARY_OPERATOR_VV(*)
    TLA_IMPLEMENT_BINARY_OPERATOR_VV(/)

    TLA_IMPLEMENT_BINARY_OPERATOR_VS(+)
    TLA_IMPLEMENT_BINARY_OPERATOR_VS(-)
    TLA_IMPLEMENT_BINARY_OPERATOR_VS(*)
    TLA_IMPLEMENT_BINARY_OPERATOR_VS(/)

    TLA_IMPLEMENT_BINARY_OPERATOR_SV(+)
    TLA_IMPLEMENT_BINARY_OPERATOR_SV(-)
    TLA_IMPLEMENT_BINARY_OPERATOR_SV(*)
    TLA_IMPLEMENT_BINARY_OPERATOR_SV(/)

    TLA_IMPLEMENT_COMPOUND_OPERATOR_VV(+=)
    TLA_IMPLEMENT_COMPOUND_OPERATOR_VV(-=)
    TLA_IMPLEMENT_COMPOUND_OPERATOR_VV(*=)
    TLA_IMPLEMENT_COMPOUND_OPERATOR_VV(/=)

    TLA_IMPLEMENT_COMPOUND_OPERATOR_VS(+=)
    TLA_IMPLEMENT_COMPOUND_OPERATOR_VS(-=)
    TLA_IMPLEMENT_COMPOUND_OPERATOR_VS(*=)
    TLA_IMPLEMENT_COMPOUND_OPERATOR_VS(/=)

    template <typename T, unsigned D>
    inline std::ostream &operator<<(std::ostream &stream, const Vector<T, D> &v)
    {
        stream << '(';
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D - 1; i++)
        {
            stream << v[i] << ", ";
        }
        stream << v[D - 1];
        stream << ')';
        return stream;
    }

    template <typename T, unsigned D>
    inline T dot(const Vector<T, D> &lhs, const Vector<T, D> &rhs) noexcept
    {
        T dotProd = T(0);
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            dotProd += (lhs[i] * rhs[i]);
        }
        return dotProd;
    }

    template <typename T>
    inline Vector<T, 3> cross(const Vector<T, 3> &lhs, const Vector<T, 3> &rhs) noexcept
    {
        Vector<T, 3> result{
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x};
        return result;
    }

    template <typename T, unsigned D>
    inline T sqrLength(const Vector<T, D> &v) noexcept
    {
        return dot(v, v);
    }

    template <typename T, unsigned D>
    inline T length(const Vector<T, D> &v) noexcept
    {
        return std::sqrt(sqrLength(v));
    }

    template <typename T, unsigned D>
    inline Vector<T, D> normalize(const Vector<T, D> &v) noexcept
    {
        T len = length(v);
        assert(len > 0);
        return v / len;
    }

    template <typename T, unsigned D>
    inline T distance(const Vector<T, D> &lhs, const Vector<T, D> &rhs) noexcept
    {
        return length(lhs - rhs);
    }

    template <typename T, unsigned D>
    inline Vector<T, D> exp(const Vector<T, D> &v) noexcept
    {
        Vector<T, D> result;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result[i] = std::exp(v[i]);
        }
        return result;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> applyUnaryOp(const Vector<T, D> &v, std::function<T(T)> op) noexcept
    {
        Vector<T, D> result;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result[i] = op(v[i]);
        }
        return result;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> applyBinaryOp(const Vector<T, D> &lhs, const Vector<T, D> &rhs, std::function<T(T, T)> op) noexcept
    {
        Vector<T, D> result;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result[i] = op(lhs[i], rhs[i]);
        }
        return result;
    }

    template <typename T>
    using Vector2 = Vector<T, 2>;
    template <typename T>
    using Vector3 = Vector<T, 3>;
    template <typename T>
    using Vector4 = Vector<T, 4>;

    using Vector2b = Vector2<bool>;
    using Vector2i = Vector2<int32_t>;
    using Vector2u = Vector2<uint32_t>;
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;

    using Vector3b = Vector3<bool>;
    using Vector3i = Vector3<int32_t>;
    using Vector3u = Vector3<uint32_t>;
    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;

    using Vector4b = Vector4<bool>;
    using Vector4i = Vector4<int32_t>;
    using Vector4u = Vector4<uint32_t>;
    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;
}
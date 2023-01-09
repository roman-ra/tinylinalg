#pragma once

#include "TlaDefs.hpp"

#include <cmath>
#include <ostream>
#include <cstdint>
#include <cassert>
#include <functional>
#include <algorithm>

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
    inline T distance(const Vector<T, D> &v1, const Vector<T, D> &v2) noexcept
    {
        return length(v2 - v1);
    }

    template <typename T, unsigned D>
    inline Vector<T, D> min(const Vector<T, D> &v1, const Vector<T, D> &v2) noexcept
    {
        Vector<T, D> result;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result[i] = std::min(v1[i], v2[i]);
        }
        return result;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> max(const Vector<T, D> &v1, const Vector<T, D> &v2) noexcept
    {
        Vector<T, D> result;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result[i] = std::max(v1[i], v2[i]);
        }
        return result;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> clamp(const Vector<T, D> &v, const Vector<T, D> &lo, const Vector<T, D> &hi) noexcept
    {
        Vector<T, D> result;
        UNROLL_LOOP(D)
        for (unsigned i = 0; i < D; i++)
        {
            result[i] = std::clamp(v[i], lo[i], hi[i]);
        }
        return result;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> mix(const Vector<T, D> &v1, const Vector<T, D> &v2, T weight) noexcept
    {
        Vector<T, D> result = v1 * (T(1) - weight) + v2 * weight;
        return result;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> faceforward(const Vector<T, D> &n, const Vector<T, D> &i, const Vector<T, D> &nRef) noexcept
    {
        if (dot(nRef, i) < 0) {
            return n;
        } else {
            return -n;
        }
    }

    template <typename T, unsigned D>
    inline Vector<T, D> reflect(const Vector<T, D> &i, const Vector<T, D> &n) noexcept
    {
        return i - T(2) * dot(n, i) * n;
    }

    template <typename T, unsigned D>
    inline Vector<T, D> refract(const Vector<T, D> &i, const Vector<T, D> &n, T r) noexcept
    {
        T d = T(1) - r * r * (T(1) - dot(n, i) * dot(n, i));
        if (d < T(0)) return Vector<T, D>{T(0)};
        return r * i - (r * dot(n, i) + std::sqrt(d)) * n;
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

    // OpenGL/GLSL-like aliases
    using bvec2 = Vector2b;
    using ivec2 = Vector2i;
    using uvec2 = Vector2u;
    using vec2 = Vector2f;
    using dvec2 = Vector2d;

    using bvec3 = Vector3b;
    using ivec3 = Vector3i;
    using uvec3 = Vector3u;
    using vec3 = Vector3f;
    using dvec3 = Vector3d;

    using bvec4 = Vector4b;
    using ivec4 = Vector4i;
    using uvec4 = Vector4u;
    using vec4 = Vector4f;
    using dvec4 = Vector4d;
}
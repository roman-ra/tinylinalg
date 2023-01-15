#pragma once

#include "TlaDefs.hpp"
#include "Vector.hpp"

#include <cmath>
#include <ostream>
#include <cstdint>
#include <cassert>
#include <functional>
#include <algorithm>

namespace tla
{
    template <typename T, unsigned D>
        requires(std::integral<T> || std::floating_point<T>)
    struct Matrix
    {
        Matrix()
        {
        }

        Matrix(T d)
        {
            UNROLL_LOOP(D)
            for (unsigned r = 0; r < D; r++)
            {
                for (unsigned c = 0; c < D; c++)
                {
                    if (r == c) {
                        columns[c][r] = d;
                    }
                }
            }
        }

        Vector<T, D> columns[D];
    };

    template <typename T, unsigned D>
    inline std::ostream &operator<<(std::ostream &stream, const Matrix<T, D> &m)
    {
        // stream << '(';
        UNROLL_LOOP(D)
        for (unsigned r = 0; r < D; r++)
        {
            for (unsigned c = 0; c < D; c++)
            {
                stream << m.columns[c][r] << " ";
            }
            stream << std::endl;
        }
        // stream << ')';
        return stream;
    }

}
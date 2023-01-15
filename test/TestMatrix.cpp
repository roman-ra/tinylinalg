#include "gtest/gtest.h"

#include "tinylinalg/Matrix.hpp"

#include <iostream>

using namespace tla;

TEST(MatrixTest, MatrixConstructors)
{
    tla::Matrix<float, 4> m{1.f};
    std::cout << m << std::endl;
}
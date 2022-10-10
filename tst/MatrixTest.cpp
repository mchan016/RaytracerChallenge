#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Matrix.h"
#include "Tuple.h"

using raytracer::Matrix;
using raytracer::Tuple;
using raytracer::TupleType;
using raytracer::PI;

TEST(MatrixTest, initMatrixTest)
{
    Matrix matrix{{
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    }};
    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][3], 4);
    EXPECT_EQ(matrix[1][0], 5.5);
    EXPECT_EQ(matrix[1][2], 7.5);
    EXPECT_EQ(matrix[2][2], 11);
    EXPECT_EQ(matrix[3][0], 13.5);
    EXPECT_EQ(matrix[3][2], 15.5);
}

TEST(MatrixTest, multiDimensionMatrixTest)
{
    // Verify can create matrix of 2x2
    Matrix matrix1{{
        {-3, 5},
        {1, -2}
    }};
    EXPECT_EQ(matrix1[0][0], -3);
    EXPECT_EQ(matrix1[0][1], 5);
    EXPECT_EQ(matrix1[1][0], 1);
    EXPECT_EQ(matrix1[1][1], -2);

    // Verify can create matrix of 3x3
    Matrix matrix2{{
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    }};
    EXPECT_EQ(matrix2[0][0], -3);
    EXPECT_EQ(matrix2[1][1], -2);
    EXPECT_EQ(matrix2[2][2], 1);
}

TEST(MatrixTest, matrixEqualityTest)
{
    Matrix matrix1{{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    }};

    Matrix matrix2{{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    }};

    Matrix matrix3{{
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    }};

    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_FALSE(matrix1 != matrix2);
    EXPECT_TRUE(matrix1 != matrix3);
}

TEST(MatrixTest, matrixMultiplicationTest)
{
    Matrix matrix1{{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    }};
    Matrix matrix2{{
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}
    }};

    Matrix matrix3{{
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    }};

    EXPECT_TRUE(matrix1 * matrix2 == matrix3);
    EXPECT_FALSE(matrix1 * matrix3 == matrix2);
}

TEST(MatrixTest, matrixTupleMultiplicationTest)
{
    Matrix matrix1{{
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    }};
    Tuple tuple1{1, 2, 3, TupleType::POINT};

    EXPECT_TRUE((matrix1 * tuple1 == Tuple{18, 24, 33, TupleType::POINT}));
    EXPECT_FALSE((matrix1 * tuple1 == Tuple{18, 24, 33, TupleType::VECTOR}));
}

TEST(MatrixTest, identityMatrixMulitplicationTest)
{
    Matrix matrix1{{
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    }};
    Tuple tuple1{1, 2, 3, TupleType::VECTOR};
    Matrix identityMatrix{{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};

    EXPECT_TRUE(matrix1 * identityMatrix == matrix1);
    EXPECT_TRUE(identityMatrix * tuple1 == tuple1);
}

TEST(MatrixTest, matrixTransposeTest)
{
    Matrix matrix1{{
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}
    }};
    Matrix matrix2{{
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}
    }};

    Matrix identityMatrix{{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    Matrix identityMatrix2{{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};

    matrix1.transpose();
    identityMatrix.transpose();
    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_TRUE(identityMatrix == identityMatrix2);
}

TEST(MatrixTest, matrixDeterminantTest)
{
    Matrix matrix1{{
        {1, 5},
        {-3, 2}
    }};

    EXPECT_EQ(matrix1.determinant(), 17);
}

TEST(MatrixTest, matrixSubmatrixTest)
{
    Matrix matrix1{{
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3}
    }};
    Matrix submatrix1{{
        {-3, 2},
        {0, 6}
    }};

    EXPECT_TRUE(matrix1.submatrix(0, 2) == submatrix1);

    Matrix matrix2{{
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    }};
    Matrix submatrix2{{
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    }};

    EXPECT_TRUE(matrix2.submatrix(2, 1) == submatrix2);
}

TEST(MatrixTest, matrixMinorTest)
{
    Matrix matrix1{{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    }};

    EXPECT_EQ(matrix1.minor(1, 0), 25);
}

TEST(MatrixTest, matrixCofactorTest)
{
    Matrix matrix1{{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    }};

    ASSERT_EQ(matrix1.minor(0, 0), -12);
    EXPECT_EQ(matrix1.cofactor(0, 0), -12);

    ASSERT_EQ(matrix1.minor(1, 0), 25);
    EXPECT_EQ(matrix1.cofactor(1, 0), -25);
}

TEST(MatrixTest, largerMatrixDeterminant)
{
    // Calculating the determinant of a 3x3 matrix
    Matrix matrix1{{
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    }};

    ASSERT_EQ(matrix1.cofactor(0, 0), 56);
    ASSERT_EQ(matrix1.cofactor(0, 1), 12);
    ASSERT_EQ(matrix1.cofactor(0, 2), -46);
    EXPECT_EQ(matrix1.determinant(), -196);

    // Calculating the determinant of a 4x4 matrix
    Matrix matrix2{{
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    }};

    ASSERT_EQ(matrix2.cofactor(0, 0), 690);
    ASSERT_EQ(matrix2.cofactor(0, 1), 447);
    ASSERT_EQ(matrix2.cofactor(0, 2), 210);
    ASSERT_EQ(matrix2.cofactor(0, 3), 51);
    EXPECT_EQ(matrix2.determinant(), -4071);
}

TEST(MatrixTest, matrixInvertibilityTest)
{
    Matrix matrix1{{
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6}
    }};

    Matrix matrix2{{
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}
    }};

    ASSERT_TRUE(matrix1.inversible());
    ASSERT_FALSE(matrix2.inversible());
}

TEST(MatrixTest, matrixInverseTest)
{
    Matrix matrix1{{
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    }};

    Matrix matrix2{{
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}
    }};

    Matrix inverseMatrix1{matrix1.inverse()};

    EXPECT_EQ(matrix1.determinant(), 532);
    EXPECT_EQ(matrix1.cofactor(2, 3), -160);
    EXPECT_EQ(inverseMatrix1[3][2], -160.0/532);
    EXPECT_EQ(matrix1.cofactor(3, 2), 105);
    EXPECT_EQ(inverseMatrix1[2][3], 105.0/532);
    EXPECT_TRUE(inverseMatrix1 == matrix2);
}

TEST(MatrixTest, matrixInverseMoreTest)
{
    Matrix matrix1{{
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    }};

    Matrix inverseMatrix1{{
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}
    }};

    EXPECT_TRUE(matrix1.inverse() == inverseMatrix1);

    Matrix matrix2{{
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    }};

    Matrix inverseMatrix2{{
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}
    }};

    EXPECT_TRUE(matrix2.inverse() == inverseMatrix2);
}

TEST(MatrixTest, matrixInverseProductTest)
{
    // Multiplying a product by the inverse of one of its
    // components returns the other original component
    Matrix matrix1{{
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    }};

    Matrix matrix2{{
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    }};

    Matrix product = matrix1 * matrix2;
    
    EXPECT_TRUE(product * matrix2.inverse() == matrix1);
}

TEST(MatrixTest, identityMatrixTest)
{
    Matrix matrix1{{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};

    Matrix matrix2{{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};

    EXPECT_TRUE(raytracer::identity(3) == matrix1);
    EXPECT_TRUE(raytracer::identity(4) == matrix2);
}

TEST(MatrixTest, matrixTranslationTest)
{
    Matrix transform{raytracer::translation(5, -3, 2)};
    Matrix inv{transform.inverse()};
    auto p{raytracer::point(-3, 4, 5)};
    auto v{raytracer::vector(-3, 4, 5)};

    EXPECT_TRUE(transform * *p == *raytracer::point(2, 1, 7));
    EXPECT_TRUE(inv * *p == *raytracer::point(-8, 7, 3));
    EXPECT_TRUE(transform * *v == *v);
}

TEST(MatrixTest, matrixScalingTest)
{
    Matrix transform{raytracer::scaling(2, 3, 4)};

    auto p{raytracer::point(-4, 6, 8)};
    auto v{raytracer::vector(-4, 6, 8)};

    EXPECT_TRUE(transform * *p == *raytracer::point(-8, 18, 32));
    EXPECT_TRUE(transform * *v == *raytracer::vector(-8, 18, 32));
    EXPECT_TRUE(transform.inverse() * *v == *raytracer::vector(-2, 2, 2));

    // Testing Reflection
    Matrix transform2{raytracer::scaling(-1, 1, 1)};
    auto p2{raytracer::point(2, 3, 4)};

    EXPECT_TRUE(transform2 * *p2 == *raytracer::point(-2, 3, 4));
}

TEST(MatrixTest, matrixRotationXTest)
{
    auto p{raytracer::point(0, 1, 0)};
    Matrix halfQtr{raytracer::rotationX(PI / 4)};
    Matrix fullQtr{raytracer::rotationX(PI / 2)};

    EXPECT_TRUE(halfQtr * *p == *raytracer::point(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
    EXPECT_TRUE(fullQtr * *p == *raytracer::point(0, 0, 1));
    EXPECT_TRUE(halfQtr.inverse() * *p == *raytracer::point(0, std::sqrt(2) / 2, -1 * std::sqrt(2) / 2));
}

TEST(MatrixTest, matrixRotationYTest)
{
    auto p{raytracer::point(0, 0, 1)};
    Matrix halfQtr{raytracer::rotationY(PI / 4)};
    Matrix fullQtr{raytracer::rotationY(PI / 2)};

    EXPECT_TRUE(halfQtr * *p == *raytracer::point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
    EXPECT_TRUE(fullQtr * *p == *raytracer::point(1, 0, 0));
}

TEST(MatrixTest, matrixRotationZTest)
{
    auto p{raytracer::point(0, 1, 0)};
    Matrix halfQtr{raytracer::rotationZ(PI / 4)};
    Matrix fullQtr{raytracer::rotationZ(PI / 2)};

    double sqrtTwoDTwo = std::sqrt(2) / 2;
    EXPECT_TRUE(halfQtr * *p == *raytracer::point(-1 * sqrtTwoDTwo, sqrtTwoDTwo, 0));
    EXPECT_TRUE(fullQtr * *p == *raytracer::point(-1, 0, 0));
}
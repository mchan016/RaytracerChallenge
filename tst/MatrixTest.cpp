#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Matrix.h"
#include "Tuple.h"

using raytracer::Matrix;
using raytracer::Tuple;
using raytracer::TupleType;

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
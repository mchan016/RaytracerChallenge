#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Matrix.h"

using raytracer::Matrix;


TEST(MatrixTest, initMatrixTest)
{
    std::vector<std::vector<double>> sample{
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    };

    Matrix matrix{std::move(sample)};
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
    std::vector<std::vector<double>> sample1{
        {-3, 5},
        {1, -2}
    };

    Matrix matrix1{std::move(sample1)};
    EXPECT_EQ(matrix1[0][0], -3);
    EXPECT_EQ(matrix1[0][1], 5);
    EXPECT_EQ(matrix1[1][0], 1);
    EXPECT_EQ(matrix1[1][1], -2);

    // Verify can create matrix of 3x3
    std::vector<std::vector<double>> sample2{
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    };

    Matrix matrix2{std::move(sample2)};
    EXPECT_EQ(matrix2[0][0], -3);
    EXPECT_EQ(matrix2[1][1], -2);
    EXPECT_EQ(matrix2[2][2], 1);
}
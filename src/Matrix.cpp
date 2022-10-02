#include "Matrix.h"

#include <vector>

using raytracer::Matrix;

Matrix::Matrix()
    : m_matrix(DEFAULT_ROWS, std::vector<double>(DEFAULT_COLUMNS, 0.0))
{}

Matrix::Matrix(int rows, int columns)
    : m_matrix(rows, std::vector<double>(columns, 0.0))
{}

Matrix::Matrix(std::vector<std::vector<double>>& matrix)
    : m_matrix{matrix}
{}

Matrix::Matrix(std::vector<std::vector<double>>&& matrix)
    : m_matrix{matrix}
{}

bool Matrix::empty() const
{
    return m_matrix.empty();
}

int Matrix::rows() const
{
    return m_matrix.size();
}

int Matrix::columns() const
{
    if (m_matrix.empty()) return 0;

    return m_matrix[0].size();
}

const std::vector<double>& Matrix::operator[](int i) const
{
    return m_matrix[i];
}

/**
 * @brief Multiplication between two matrices. Calculation is only based on
 * matrices that are 4X4
 * 
 * @param rhs 
 * @return Matrix 
 */
Matrix Matrix::operator*(const Matrix& rhs) const
{
    std::vector<std::vector<double>> product{};

    for (int i = 0; i < rows(); i++)
    {
        std::vector<double> row{};
        for (int j = 0; j < columns(); j++)
        {
            double result = this->m_matrix[i][0] * rhs.m_matrix[0][j]
                        + this->m_matrix[i][1] * rhs.m_matrix[1][j]
                        + this->m_matrix[i][2] * rhs.m_matrix[2][j]
                        + this->m_matrix[i][3] * rhs.m_matrix[3][j];
            
            row.push_back(result);
        }
        product.push_back(row);
    }

    return Matrix{product};
}
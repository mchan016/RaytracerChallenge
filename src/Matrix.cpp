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

const std::vector<std::vector<double>>& Matrix::matrix() const
{
    return m_matrix;
}

const std::vector<double>& Matrix::operator[](int i) const
{
    return m_matrix[i];
}
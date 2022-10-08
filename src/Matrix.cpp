#include "Matrix.h"
#include "Tuple.h"
#include "RaytracerUtils.h"

#include <vector>
#include <stdexcept>
#include <string>

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

std::vector<double>& Matrix::operator[](int i)
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

/**
 * @brief Multiplies a 4X4 matrix by a Tuple and returns a Tuple
 * 
 * @param rhs 
 * @throw Throws an invalid argument exception if matrix dimension is not 4X4
 * @return raytracer::Tuple 
 */
raytracer::Tuple Matrix::operator*(const raytracer::Tuple& rhs) const
{
    if (rows() != DEFAULT_ROWS || columns() != DEFAULT_COLUMNS)
    {
        throw new std::invalid_argument("Matrix is not 4 X 4");
    }

    std::vector<double> product{};
    for (int i = 0; i < rows(); i++)
    {
        double prod = this->m_matrix[i][0] * rhs.x()
                    + this->m_matrix[i][1] * rhs.y()
                    + this->m_matrix[i][2] * rhs.z()
                    + this->m_matrix[i][3] * static_cast<int>(rhs.type());

        product.push_back(prod);
    }

    TupleType type = static_cast<TupleType>(static_cast<int>(product[3]));
    return Tuple{product[0], product[1], product[2], type};
}

/**
 * @brief Transposes the current matrix's rows to columns and columns to rows
 *          in place.
 * 
 * @return true 
 * @return false 
 */
void Matrix::transpose()
{
    std::vector<std::vector<double>> copied{m_matrix};
    
    // Transpose back to original matrix
    for (int i = 0; i < copied.size(); i++)
    {
        for (int j = 0; j < copied[i].size(); j++)
        {
            m_matrix[j][i] = copied[i][j];
        }
    }
}

double Matrix::determinant() const
{
    double result{};

    if (rows() == 2)
    {
        result = m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
    }
    else
    {
        for (int i = 0; i < columns(); i++)
        {
            result += m_matrix[0][i] * cofactor(0, i);
        }
    }

    return result;
}

Matrix Matrix::submatrix(int row, int column) const
{
    if (row < 0 || row >= rows() || column < 0 || column >= columns())
    {
        std::string msg = "Selected row: " + std::to_string(row) 
                        + " or column: " + std::to_string(column) 
                        + " doesn't exist";
        throw new std::invalid_argument(msg);
    }

    Matrix result{rows()-1, columns()-1};
    for (int i = 0, x = 0; i < rows(); i++)
    {
        if (i == row) continue;
        
        for (int j = 0, y = 0; j < columns(); j++)
        {
            if (j == column) continue;
            result[x][y] = m_matrix[i][j];
            ++y;
        }

        ++x;
    }

    return result;
}

double Matrix::minor(int row, int column) const
{
    return submatrix(row, column).determinant();
}

double Matrix::cofactor(int row, int column) const
{
    double matrixMinor = minor(row, column);
    return (row + column) % 2 == 0 ? matrixMinor : matrixMinor * -1;
}

/**
 * @brief Inversible if determinant of matrix does not equal 0
 * 
 * @return true Determinant is any number that is not 0
 * @return false Determinant equals 0
 */
bool Matrix::inversible() const
{
    return inversible(determinant());
}

/**
 * @brief Inversible that accepts a determinant number and check whether
 *          the number fits into the inversibility criteria
 * 
 * @param determinant 
 * @return true 
 * @return false 
 */
bool Matrix::inversible(double determinant) const
{
    return !doubleEqual(determinant, 0);
}

/**
 * @brief Calculates and returns the inverse matrix
 * 
 * @throw An invalid_argument exception if a matrix is not inversible
 * @return Matrix The inverse matrix of the current matrix, if reversible
 */
Matrix Matrix::inverse() const
{
    if (!inversible())
    {
        throw new std::invalid_argument("Matrix cannot be inversed");
    }

    Matrix result{rows(), columns()};

    double d = determinant();
    for (int i = 0; i < rows(); i++)
    {
        for (int j = 0; j < columns(); j++)
        {
            double c = cofactor(i, j);
            result[j][i] = c / d;
        }
    }

    return result;
}

////////////////////////////////////
// FACTORY FUNCTIONS
////////////////////////////////////

/**
 * @brief Create an identity matrix that is dimension x dimension in size
 * 
 * @param dimension The number of rows and columns of the matrix 
 * @return Matrix An identity matrix of dimension x dimension
 */
Matrix raytracer::identity(int dimension) noexcept
{
    Matrix identity{dimension, dimension};
    int index{0};
    while (index < dimension)
    {
        identity[index][index] = 1;
        ++index;
    }

    return identity;
}

Matrix raytracer::translation(double x, double y, double z) noexcept
{
    // Get a 4x4 identity matrix
    Matrix transMatrix{identity(Matrix::DEFAULT_ROWS)};

    // Add in the translations for x, y, and z
    transMatrix[0][3] = x;
    transMatrix[1][3] = y;
    transMatrix[2][3] = z;

    return transMatrix;
}
#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

#include "Tuple.h"
#include "RaytracerUtils.h"

#include <iostream>
#include <vector>

namespace raytracer
{
    class Matrix
    {
    private:
        std::vector<std::vector<double>> m_matrix;

    public:
        static constexpr int DEFAULT_ROWS = 4;
        static constexpr int DEFAULT_COLUMNS = 4;

        Matrix();
        Matrix(int rows, int columns);
        Matrix(std::vector<std::vector<double>>& matrix);
        Matrix(std::vector<std::vector<double>>&& matrix);

        bool empty() const;
        int rows() const;
        int columns() const;

        const std::vector<double>& operator[](int i) const;
        Matrix operator*(const Matrix& rhs) const;
        Tuple operator*(const Tuple& rhs) const;

        void transpose();
        double determinant() const;
        Matrix submatrix(int row, int column) const;
        double minor(int row, int column) const;
        double cofactor(int row, int column) const;
        bool inversible() const;
        bool inversible(double determinant) const;
        Matrix inverse() const;
    }; // Matrix


    ////////////////////////////////////
    // OPERATOR OVERLOADS
    ////////////////////////////////////
    inline bool operator==(const Matrix& lhs, const Matrix& rhs)
    {
        if (lhs.empty() && rhs.empty()) return true;
        if (lhs.empty() || rhs.empty()) return false;

        bool isEqual = true;
        for (int i = 0; i < lhs.rows(); i++)
        {
            for (int j = 0; j < lhs.columns(); j++)
            {
                if (!doubleEqual(lhs[i][j], rhs[i][j]))
                {
                    isEqual = false;
                    break;
                }
            }
        }

        return isEqual;
    }

    inline bool operator!=(const Matrix& lhs, const Matrix& rhs)
    {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const Matrix& mtrx)
    {
        for (int i = 0; i < mtrx.rows(); i++)
        {
            for (int j = 0; j < mtrx.columns(); j++)
            {
                os << mtrx[i][j] << ' ';
            }
            os << '\n';
        }

        return os;
    }
} // namespace raytracer


#endif // RAYTRACER_MATRIX_H
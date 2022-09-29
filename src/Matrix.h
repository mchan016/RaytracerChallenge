#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

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

        const std::vector<std::vector<double>>& matrix() const;

        const std::vector<double>& operator[](int i) const;
    }; // Matrix
    
} // namespace raytracer


#endif // RAYTRACER_MATRIX_H
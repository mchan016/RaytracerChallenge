#include "Canvas.h"
#include "Tuple.h"

#include <vector>
#include <stdexcept>


raytracer::Canvas::Canvas()
    : m_canvas{}
{}

raytracer::Canvas::Canvas(int width, int height)
    : m_canvas{}
{
    for (int i = 0; i < height; i++)
    {
        std::vector<Tuple> v{};
        for (int j = 0; j < width; j++)
        {
            v.push_back(raytracer::Tuple{0, 0, 0, TupleType::COLOR});
        }
        m_canvas.push_back(v);
    }
}

int raytracer::Canvas::width() const
{
    return height() == 0 ? 0 : static_cast<int>(m_canvas.at(0).size());
}

int raytracer::Canvas::height() const
{
    return static_cast<int>(m_canvas.size());
}

const std::vector<std::vector<raytracer::Tuple>>& raytracer::Canvas::canvas() const
{
    return m_canvas;
}

/**
 * @brief Gets the pixel at [row, column] position.  Throws an exception if position
 *        is out of range.
 * 
 * @param row 
 * @param column 
 * @return const raytracer::Tuple& - The color pixel at [row, column]
 */
const raytracer::Tuple& raytracer::Canvas::pixel(int row, int column) const
{
    // Verify within range
    if (pixelOutOfBounds(row, column))
    {
        throw new std::out_of_range("Arguments outside bounds of canvas dimension");
    }

    return m_canvas[row][column];
}

/**
 * @brief Sets the color pixel at position [row, column] of the canvas to the 
 * color pixel input
 * 
 * @param row 
 * @param column 
 * @param color 
 * @return true - Color pixel was successfully set
 * @return false - Color pixel was not successfully set, which could be due to out of bounds or Tuple not a color
 */
bool raytracer::Canvas::pixel(int row, int column, const raytracer::Tuple& color)
{
    if (pixelOutOfBounds(row, column) || color.type() != TupleType::COLOR)
        return false;

    m_canvas[row][column] = color;
    return true;
}

/**
 * @brief Given a row and column coordinate of a pixel check whether
 * the pixel is out of bounds of the canvas
 * 
 * @param row 
 * @param column 
 * @return true Pixel is out of bounds
 * @return false Pixel is not out of bounds
 */
bool raytracer::Canvas::pixelOutOfBounds(int row, int column) const
{
    return row >= height() 
        || row < 0
        || column >= width()
        || column < 0;
}

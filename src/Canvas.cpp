#include "Canvas.h"
#include "Tuple.h"

#include <cmath>
#include <vector>
#include <stdexcept>
#include <string>

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
 * @brief Gets the pixel at [x, y] position on the canvas.  Throws an exception if position
 *        is out of range.
 * 
 * @param x - The x-coordinate of the canvas.  Corresponds to the column position of the y-th row
 * @param y - The y-coordinate of the canvas.  Corresponds to the row position of the x-th column
 * @return const raytracer::Tuple& - The color pixel at [x, y]
 */
const raytracer::Tuple& raytracer::Canvas::pixel(int x, int y) const
{
    // Verify within range
    if (pixelOutOfBounds(x, y))
    {
        throw new std::out_of_range("Arguments outside bounds of canvas dimension");
    }

    return m_canvas[y][x];
}

/**
 * @brief Sets the color pixel at position [x, y] on the canvas to the color pixel input
 * returns true if the pixel is successfully set, otherwise false
 * 
 * @param x - The x-coordinate of the canvas.  Corresponds to the column position of the y-th row
 * @param y - The y-coordinate of the canvas.  Corresponds to the row position of the x-th column
 * @param color - The new pixel color to be set
 * @return true - Color pixel was successfully set
 * @return false - Color pixel was not successfully set, which could be due to out of bounds or Tuple not a color
 */
bool raytracer::Canvas::pixel(int x, int y, const raytracer::Tuple& color)
{
    if (pixelOutOfBounds(x, y) || color.type() != TupleType::COLOR)
        return false;

    m_canvas[y][x] = color;
    return true;
}

/**
 * @brief Given a row and column coordinate of a pixel check whether
 * the pixel is out of bounds of the canvas
 * 
 * @param x - The x-coordinate of the canvas.  Corresponds to the column position of the y-th row
 * @param y - The y-coordinate of the canvas.  Corresponds to the row position of the x-th column
 * @return true Pixel is out of bounds
 * @return false Pixel is not out of bounds
 */
bool raytracer::Canvas::pixelOutOfBounds(int x, int y) const
{
    return y >= height() 
        || y < 0
        || x >= width()
        || x < 0;
}

std::string raytracer::Canvas::canvasToPPM() const
{
    // Generate Header
    std::string ppm{};
    ppm += "P3\n";
    ppm += std::to_string(width()) + " " + std::to_string(height()) + '\n';
    ppm += std::to_string(COLOR_SCALE) += '\n';

    // Generate Canvas Body
    for (const auto& pixels : m_canvas)
    {
        for (const auto& pixel : pixels)
        {
            ppm += std::to_string(clipPixelVal(pixel.x())) + ' ';
            ppm += std::to_string(clipPixelVal(pixel.y())) + ' ';
            ppm += std::to_string(clipPixelVal(pixel.z())) + '\n';
        }
    }

    return ppm;
}

int raytracer::Canvas::clipPixelVal(double pixelVal) const
{
    double scale = static_cast<double>(COLOR_SCALE);
    pixelVal *= scale;

    if (pixelVal < 0.0)
        return 0;
    else if (pixelVal > scale)
        return COLOR_SCALE;
    
    return std::round(pixelVal);
}
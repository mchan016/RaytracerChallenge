#include "Canvas.h"
#include "Tuple.h"

#include <vector>


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
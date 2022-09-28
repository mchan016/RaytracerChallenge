#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H

#include "Tuple.h"

#include <vector>

namespace raytracer
{
    class Canvas
    {
    private:
        std::vector<std::vector<Tuple>> m_canvas;

    public:
        Canvas();
        Canvas(int width, int height);

        int width() const;
        int height() const;
        const std::vector<std::vector<Tuple>>& canvas() const;

        const Tuple& pixel(int row, int column) const;
        bool pixel(int row, int column, const Tuple& color);

    private:
        bool pixelOutOfBounds(int row, int column) const;
    };
} // namespace raytracer


#endif // RAYTRACER_CANVAS_H
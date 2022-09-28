#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H

#include "Tuple.h"

#include <vector>
#include <string>

namespace raytracer
{
    class Canvas
    {
    private:
        std::vector<std::vector<Tuple>> m_canvas;

    public:
        static constexpr int COLOR_SCALE = 255;

        Canvas();
        Canvas(int width, int height);

        int width() const;
        int height() const;
        const std::vector<std::vector<Tuple>>& canvas() const;

        const Tuple& pixel(int x, int y) const;
        bool pixel(int x, int y, const Tuple& color);
        std::string canvasToPPM() const;

    private:
        bool pixelOutOfBounds(int x, int y) const;
        int clipPixelVal(double pixelVal) const;
        
    };
} // namespace raytracer


#endif // RAYTRACER_CANVAS_H
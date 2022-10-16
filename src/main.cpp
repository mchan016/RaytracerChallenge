#include "Canvas.h"
#include "Tuple.h"
#include "Matrix.h"
#include "RaytracerUtils.h"

#include <iostream>

using raytracer::Tuple;
using raytracer::TupleType;
using raytracer::PI;

int main()
{
    raytracer::Canvas canvas{800, 800};

    // Turn entire canvas to yellow
    // auto yellow = raytracer::color(1, 0.92, 0);
    // for (int row = 0; row < canvas.canvas().size(); row++)
    // {
    //     for (int col = 0; col < canvas.canvas().at(0).size(); col++)
    //     {
    //         canvas.pixel(col, row, *yellow);
    //     }
    // }

    // canvas.ppmToFile();

    /**
     * @brief Create a clock using matrix transforms
     * 
     */
    // Get midpoint and set radius
    Tuple midCanvas{static_cast<double>(canvas.width() / 2.0), 
                    static_cast<double>(canvas.height() / 2.0), 
                    0, TupleType::POINT};
    Tuple twelveOClock{0, 1, 0, TupleType::POINT};
    double radius{static_cast<double>(3 * canvas.height() / 8.0)};
    auto yellow = raytracer::color(1, 0.92, 0);
    auto rotateNext{raytracer::rotationZ(PI / 6)};


    std::cout << "radius: " << std::to_string(radius) << '\n';
    std::cout << "mid canvas: " << midCanvas << '\n';
    canvas.pixel(midCanvas.x(), midCanvas.y(), *raytracer::color(1, 1, 1));
    canvas.pixel(midCanvas.x()+1, midCanvas.y(), *raytracer::color(1, 1, 1));
    canvas.pixel(midCanvas.x(), midCanvas.y()+1, *raytracer::color(1, 1, 1));
    canvas.pixel(midCanvas.x()+1, midCanvas.y()+1, *raytracer::color(1, 1, 1));
    for (int i = 1; i <= 12; i++) {
        auto rotateNext{raytracer::rotationZ(i * PI / 6)};
        auto currPoint{rotateNext * twelveOClock};

        currPoint = Tuple{currPoint.x() * radius + midCanvas.x(), 
                          currPoint.y() * radius + midCanvas.y(), 
                          0, TupleType::POINT};

        // Paint out the pixel
        std::cout << "Current Point: " << currPoint << '\n';

        int col{static_cast<int>(currPoint.x())};
        int row{static_cast<int>(currPoint.y())};
        canvas.pixel(col, row, *yellow);
        canvas.pixel(col+1, row, *yellow);
        canvas.pixel(col, row+1, *yellow);
        canvas.pixel(col+1, row+1, *yellow);
    }

    canvas.ppmToFile();

    return 0;
}
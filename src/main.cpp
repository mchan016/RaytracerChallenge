#include "Canvas.h"
#include "Tuple.h"

#include <iostream>

int main()
{
    raytracer::Canvas canvas{800, 500};

    // Turn entire canvas to yellow
    auto yellow = raytracer::color(1, 0.92, 0);
    for (int row = 0; row < canvas.canvas().size(); row++)
    {
        for (int col = 0; col < canvas.canvas().at(0).size(); col++)
        {
            canvas.pixel(col, row, *yellow);
        }
    }

    canvas.ppmToFile();

    return 0;
}
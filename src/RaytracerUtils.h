#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <cmath>

namespace raytracer
{
    constexpr double EPSILON = 0.00001;
    const double PI = std::acos(-1);
    
    bool doubleEqual(double a, double b);
}

#endif // RAYTRACER_UTILS_H
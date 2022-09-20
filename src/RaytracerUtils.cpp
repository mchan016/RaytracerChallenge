#include "RaytracerUtils.h"

#include <cmath>

bool Raytracer::doubleEqual(double a, double b)
{
    return std::abs(a - b) < Raytracer::EPSILON;
}
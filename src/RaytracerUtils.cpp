#include "RaytracerUtils.h"

#include <cmath>

bool raytracer::doubleEqual(double a, double b)
{
    return std::abs(a - b) < raytracer::EPSILON;
}
#include <memory>

#include "Shapes.h"
#include "Tuple.h"

using raytracer::Tuple;
using raytracer::TupleType;
using raytracer::Shape;
using raytracer::Sphere;


Tuple Shape::origin() const
{
    return *m_origin;
}

void Shape::origin(const Tuple& loc)
{
    if (loc.type() == TupleType::POINT)
        *m_origin = loc;
}

Sphere::Sphere()
    : m_radius{DEFAULT_RADIUS}
{}

Sphere::Sphere(double radius)
    : m_radius{radius}
{}

Sphere::Sphere(const Sphere& other)
    : m_radius{other.m_radius}
{
    origin(other.origin());
}

Sphere& Sphere::operator=(const Sphere& other)
{
    m_radius = other.m_radius;
    origin(other.origin());
}

/**
 * @brief Creates a unique default sphere
 * 
 * @return Sphere with a default origin and radius
 */
Sphere raytracer::sphere()
{
    return Sphere{};
}
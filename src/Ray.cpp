#include "Ray.h"
#include "Tuple.h"

using raytracer::Ray;
using raytracer::Tuple;


Ray::Ray()
    : m_origin{raytracer::point(0,0,0)}, m_direction{raytracer::vector(0,0,0)}
{}

Ray::Ray(std::unique_ptr<Tuple> origin, std::unique_ptr<Tuple> direction)
    : m_origin{std::move(origin)}, m_direction{std::move(direction)}
{}

Tuple Ray::origin() const
{
    return *m_origin;
}

Tuple Ray::direction() const
{
    return *m_direction;
}

Tuple Ray::position(double t) const
{
    return *(*m_origin + *(*m_direction * t));
}
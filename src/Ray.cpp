#include "Ray.h"
#include "Tuple.h"

#include <memory>

using raytracer::Ray;
using raytracer::Tuple;


Ray::Ray()
    : m_origin{std::make_unique<Tuple>(raytracer::point(0,0,0))}, 
      m_direction{std::make_unique<Tuple>(raytracer::vector(0,0,0))}
{}

Ray::Ray(Tuple origin, Tuple direction)
    : m_origin{std::make_unique<Tuple>(origin)}, m_direction{std::make_unique<Tuple>(direction)}
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
    return *m_origin + (*m_direction * t);
}
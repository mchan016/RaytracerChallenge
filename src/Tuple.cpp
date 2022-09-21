#include "Tuple.h"

#include <memory>

Raytracer::Tuple::Tuple(double x, double y, double z, TupleType type)
    : m_x{x}, m_y{y}, m_z{z}, m_type{type}
{}

double Raytracer::Tuple::x() const
{
    return m_x;
}

double Raytracer::Tuple::y() const
{
    return m_y;
}

double Raytracer::Tuple::z() const
{
    return m_z;
}

Raytracer::TupleType Raytracer::Tuple::type() const
{
    return m_type;
}

std::unique_ptr<Raytracer::Tuple> Raytracer::point(double x, double y, double z)
{
    return std::make_unique<Raytracer::Tuple>(x, y, z, Raytracer::TupleType::POINT);
}

std::unique_ptr<Raytracer::Tuple> Raytracer::vector(double x, double y, double z)
{
    return std::make_unique<Raytracer::Tuple>(x, y, z, Raytracer::TupleType::VECTOR);
}
#include "Tuple.h"

#include <memory>
#include <cmath>

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

std::unique_ptr<Raytracer::Tuple> Raytracer::color(double x, double y, double z)
{
    return std::make_unique<Raytracer::Tuple>(x, y, z, Raytracer::TupleType::COLOR);
}

std::unique_ptr<Raytracer::Tuple> Raytracer::Tuple::operator-() const
{
    return std::make_unique<Tuple>(-m_x, -m_y, -m_z, m_type);
}

std::unique_ptr<Raytracer::Tuple> Raytracer::Tuple::operator*(const double multiplier) const
{
    return std::make_unique<Tuple>(m_x*multiplier, m_y*multiplier, m_z* multiplier, m_type);
}

std::unique_ptr<Raytracer::Tuple> Raytracer::Tuple::operator/(const double divisor) const
{
    return std::make_unique<Tuple>(m_x/divisor, m_y/divisor, m_z/divisor, m_type);
}

double Raytracer::Tuple::magnitude() const
{
    return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

std::unique_ptr<Raytracer::Tuple> Raytracer::Tuple::normalize() const
{
    double mag = magnitude();

    return doubleEqual(mag, 0.0)
        ? nullptr
        : std::make_unique<Tuple>(m_x/mag, m_y/mag, m_z/mag, m_type);
}

double Raytracer::dot(const Tuple& t1, const Tuple& t2)
{
    return t1.x() * t2.x()
         + t1.y() * t2.y()
         + t1.z() * t2.z();
}

std::unique_ptr<Raytracer::Tuple> Raytracer::cross(const Raytracer::Tuple& t1, const Raytracer::Tuple& t2)
{
    return vector(
        t1.y() * t2.z() - t1.z() * t2.y(),
        t1.z() * t2.x() - t1.x() * t2.z(),
        t1.x() * t2.y() - t1.y() * t2.x()
    );
}
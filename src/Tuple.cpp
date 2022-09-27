#include "Tuple.h"

#include <memory>
#include <cmath>

raytracer::Tuple::Tuple(double x, double y, double z, TupleType type)
    : m_x{x}, m_y{y}, m_z{z}, m_type{type}
{}

double raytracer::Tuple::x() const
{
    return m_x;
}

double raytracer::Tuple::y() const
{
    return m_y;
}

double raytracer::Tuple::z() const
{
    return m_z;
}

raytracer::TupleType raytracer::Tuple::type() const
{
    return m_type;
}

std::unique_ptr<raytracer::Tuple> raytracer::point(double x, double y, double z)
{
    return std::make_unique<raytracer::Tuple>(x, y, z, raytracer::TupleType::POINT);
}

std::unique_ptr<raytracer::Tuple> raytracer::vector(double x, double y, double z)
{
    return std::make_unique<raytracer::Tuple>(x, y, z, raytracer::TupleType::VECTOR);
}

std::unique_ptr<raytracer::Tuple> raytracer::color(double x, double y, double z)
{
    return std::make_unique<raytracer::Tuple>(x, y, z, raytracer::TupleType::COLOR);
}

std::unique_ptr<raytracer::Tuple> raytracer::Tuple::operator-() const
{
    return std::make_unique<Tuple>(-m_x, -m_y, -m_z, m_type);
}

std::unique_ptr<raytracer::Tuple> raytracer::Tuple::operator*(const double multiplier) const
{
    return std::make_unique<Tuple>(m_x*multiplier, m_y*multiplier, m_z* multiplier, m_type);
}

std::unique_ptr<raytracer::Tuple> raytracer::Tuple::operator*(const raytracer::Tuple& rhs) const
{
    return std::make_unique<Tuple>(this->m_x*rhs.m_x, this->m_y*rhs.m_y, this->m_z*rhs.m_z, this->m_type);
}

std::unique_ptr<raytracer::Tuple> raytracer::Tuple::operator/(const double divisor) const
{
    return std::make_unique<Tuple>(m_x/divisor, m_y/divisor, m_z/divisor, m_type);
}

double raytracer::Tuple::magnitude() const
{
    return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

std::unique_ptr<raytracer::Tuple> raytracer::Tuple::normalize() const
{
    double mag = magnitude();

    return doubleEqual(mag, 0.0)
        ? nullptr
        : std::make_unique<Tuple>(m_x/mag, m_y/mag, m_z/mag, m_type);
}

double raytracer::dot(const Tuple& t1, const Tuple& t2)
{
    return t1.x() * t2.x()
         + t1.y() * t2.y()
         + t1.z() * t2.z();
}

std::unique_ptr<raytracer::Tuple> raytracer::cross(const raytracer::Tuple& t1, const raytracer::Tuple& t2)
{
    return vector(
        t1.y() * t2.z() - t1.z() * t2.y(),
        t1.z() * t2.x() - t1.x() * t2.z(),
        t1.x() * t2.y() - t1.y() * t2.x()
    );
}
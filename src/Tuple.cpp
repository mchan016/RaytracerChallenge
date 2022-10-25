#include "Tuple.h"

#include <cmath>

using raytracer::Tuple;
using raytracer::TupleType;

Tuple::Tuple(double x, double y, double z, TupleType type)
    : m_x{x}, m_y{y}, m_z{z}, m_type{type}
{}

Tuple::Tuple(const Tuple& other)
    : m_x{other.m_x}, m_y{other.m_y}, m_z{other.m_z}, m_type{other.m_type}
{}

Tuple& Tuple::operator=(const Tuple& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    m_type = other.m_type;

    return *this;
}

double Tuple::x() const
{
    return m_x;
}

double Tuple::y() const
{
    return m_y;
}

double Tuple::z() const
{
    return m_z;
}

TupleType Tuple::type() const
{
    return m_type;
}

Tuple raytracer::point(double x, double y, double z)
{
    return Tuple{x, y, z, raytracer::TupleType::POINT};
}

Tuple raytracer::vector(double x, double y, double z)
{
    return Tuple{x, y, z, raytracer::TupleType::VECTOR};
}

Tuple raytracer::color(double x, double y, double z)
{
    return Tuple{x, y, z, raytracer::TupleType::COLOR};
}

Tuple Tuple::operator-() const
{
    return Tuple{-m_x, -m_y, -m_z, m_type};
}

Tuple Tuple::operator*(const double multiplier) const
{
    return Tuple{m_x*multiplier, m_y*multiplier, m_z* multiplier, m_type};
}

Tuple Tuple::operator*(const Tuple& rhs) const
{
    return Tuple{this->m_x*rhs.m_x, this->m_y*rhs.m_y, this->m_z*rhs.m_z, this->m_type};
}

Tuple Tuple::operator/(const double divisor) const
{
    return Tuple{m_x/divisor, m_y/divisor, m_z/divisor, m_type};
}

double Tuple::magnitude() const
{
    return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

Tuple raytracer::Tuple::normalize() const
{
    double mag = magnitude();

    return doubleEqual(mag, 0.0)
        ? Tuple{}
        : Tuple(m_x/mag, m_y/mag, m_z/mag, m_type);
}

double raytracer::dot(const Tuple& t1, const Tuple& t2)
{
    return t1.x() * t2.x()
         + t1.y() * t2.y()
         + t1.z() * t2.z();
}

Tuple raytracer::cross(const Tuple& t1, const Tuple& t2)
{
    return vector(
        t1.y() * t2.z() - t1.z() * t2.y(),
        t1.z() * t2.x() - t1.x() * t2.z(),
        t1.x() * t2.y() - t1.y() * t2.x()
    );
}
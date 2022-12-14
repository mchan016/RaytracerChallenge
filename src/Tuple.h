#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H

#include "RaytracerUtils.h"

#include <iostream>

namespace raytracer
{
    enum class TupleType
    {
        VECTOR = 0,
        POINT,
        COLOR
    };

    class Tuple
    {
    private:
        double m_x = 0.0;
        double m_y = 0.0;
        double m_z = 0.0;
        TupleType m_type = TupleType::POINT;

    public:
        Tuple() = default;
        Tuple(double x, double y, double z, TupleType type);
        Tuple(const Tuple& other);
        Tuple& operator=(const Tuple& other);

        double x() const;
        double y() const;
        double z() const;
        TupleType type() const;

        Tuple operator-() const;
        Tuple operator*(const double multiplier) const;
        Tuple operator*(const Tuple& rhs) const;
        Tuple operator/(const double divisor) const;

        double magnitude() const;
        Tuple normalize() const;
    };

    ////////////////////////////////////
    // FACTORY FUNCTIONS
    ////////////////////////////////////
    Tuple point(double x, double y, double z);
    Tuple vector(double x, double y, double z);
    Tuple color(double x, double y, double z);

    ////////////////////////////////////
    // OPERATOR OVERLOADS
    ////////////////////////////////////
    inline bool operator==(const Tuple& lhs, const Tuple& rhs)
    {
        return doubleEqual(lhs.x(), rhs.x())
            && doubleEqual(lhs.y(), rhs.y()) 
            && doubleEqual(lhs.z(), rhs.z())
            && lhs.type() == rhs.type();
    }

    /**
     * @brief Addition operator overload for adding two tuples together.  The tuples
     *        can only be either "vector + vector" or "vector + point" or "color + color"
     * 
     * @param lhs 
     * @param rhs 
     * @return Tuple - Returns a default Tuple if the tuples could not
     *                                  be added together
     */
    inline Tuple operator+(const Tuple& lhs, const Tuple& rhs)
    {
        auto lhsType = lhs.type();
        auto rhsType = rhs.type();
        auto x = lhs.x() + rhs.x();
        auto y = lhs.y() + rhs.y();
        auto z = lhs.z() + rhs.z();

        if (lhsType == TupleType::VECTOR && rhsType == TupleType::VECTOR)
        {
            return vector(x, y, z);
        }
        else if (
            (lhsType == TupleType::POINT && rhsType == TupleType::VECTOR) || 
            (lhsType == TupleType::VECTOR && rhsType == TupleType::POINT)
        )
        {
            return point(x, y, z);
        }
        else if (lhsType == TupleType::COLOR && rhsType == TupleType::COLOR)
        {
            return color(x, y, z);
        }

        return Tuple{};
    }

    inline Tuple operator-(const Tuple& lhs, const Tuple& rhs)
    {
        auto lhsType = lhs.type();
        auto rhsType = rhs.type();
        auto x = lhs.x() - rhs.x();
        auto y = lhs.y() - rhs.y();
        auto z = lhs.z() - rhs.z();

        if (lhsType== TupleType::POINT && rhsType == TupleType::POINT)
        {
            return vector(x, y, z);
        }
        else if (lhsType == TupleType::POINT && rhsType == TupleType::VECTOR)
        {
            return point(x, y, z);
        }
        else if (lhsType == TupleType::VECTOR && rhsType == TupleType::VECTOR)
        {
            return vector(x, y, z);
        }
        else if (lhsType == TupleType::COLOR && rhsType == TupleType::COLOR)
        {
            return color(x, y, z);
        }

        return Tuple{};
    }

    inline Tuple operator*(const double multiplier, const Tuple& rhs)
    {
        return rhs * multiplier;
    }

    inline std::ostream& operator<<(std::ostream& os, const Tuple& tp)
    {
        os << "x: " << std::to_string(tp.x()) << " | ";
        os << "y: " << std::to_string(tp.y()) << " | ";
        os << "z: " << std::to_string(tp.z()) << " | ";

        return os;
    }

    ////////////////////////////////////
    // RELATED OPERATIONS
    ////////////////////////////////////
    double dot(const Tuple& t1, const Tuple& t2);
    Tuple cross(const Tuple& t1, const Tuple& t2);
} // namespace raytracer

#endif // RAYTRACER_TUPLE_H
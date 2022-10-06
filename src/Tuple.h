#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H

#include "RaytracerUtils.h"

#include <memory>

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

        double x() const;
        double y() const;
        double z() const;
        TupleType type() const;

        std::unique_ptr<Tuple> operator-() const;
        std::unique_ptr<Tuple> operator*(const double multiplier) const;
        std::unique_ptr<Tuple> operator*(const Tuple& rhs) const;
        std::unique_ptr<Tuple> operator/(const double divisor) const;

        double magnitude() const;
        std::unique_ptr<Tuple> normalize() const;
    };

    ////////////////////////////////////
    // FACTORY FUNCTIONS
    ////////////////////////////////////
    std::unique_ptr<Tuple> point(double x, double y, double z);
    std::unique_ptr<Tuple> vector(double x, double y, double z);
    std::unique_ptr<Tuple> color(double x, double y, double z);

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
     * @return std::unique_ptr<Tuple> - Returns a nullptr if the tuples could not
     *                                  be added together
     */
    inline std::unique_ptr<Tuple> operator+(const Tuple& lhs, const Tuple& rhs)
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

        return nullptr;
    }

    inline std::unique_ptr<Tuple> operator-(const Tuple& lhs, const Tuple& rhs)
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

        return nullptr;
    }

    inline std::unique_ptr<Tuple> operator*(const double multiplier, const Tuple& rhs)
    {
        return rhs * multiplier;
    }

    ////////////////////////////////////
    // RELATED OPERATIONS
    ////////////////////////////////////
    double dot(const Tuple& t1, const Tuple& t2);
    std::unique_ptr<Tuple> cross(const Tuple& t1, const Tuple& t2);
} // namespace raytracer

#endif // RAYTRACER_TUPLE_H
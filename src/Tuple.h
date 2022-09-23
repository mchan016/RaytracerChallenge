#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H

#include "RaytracerUtils.h"

#include <memory>

namespace Raytracer
{
    enum class TupleType
    {
        POINT,
        VECTOR
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
        std::unique_ptr<Tuple> operator/(const double divisor) const;

        double magnitude() const;
        std::unique_ptr<Tuple> normalize() const;
    };

    ////////////////////////////////////
    // FACTORY FUNCTIONS
    ////////////////////////////////////
    std::unique_ptr<Tuple> point(double x, double y, double z);
    std::unique_ptr<Tuple> vector(double x, double y, double z);

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
     *        can only be either "vector + vector" or "vector + point"
     * 
     * @param lhs 
     * @param rhs 
     * @return std::unique_ptr<Tuple> - Returns a nullptr if the tuples could not
     *                                  be added together
     */
    inline std::unique_ptr<Tuple> operator+(const Tuple& lhs, const Tuple& rhs)
    {
        // When both tuples are vectors
        if (lhs.type() == TupleType::VECTOR && rhs.type() == TupleType::VECTOR)
        {
            return vector(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
        }
        else if (
            (lhs.type() == TupleType::POINT && rhs.type() == TupleType::VECTOR) || 
            (lhs.type() == TupleType::VECTOR && rhs.type() == TupleType::POINT)
        )
        {
            return point(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
        }

        return nullptr;
    }

    inline std::unique_ptr<Tuple> operator-(const Tuple& lhs, const Tuple& rhs)
    {
        if (lhs.type() == TupleType::POINT && rhs.type() == TupleType::POINT)
        {
            return vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
        }
        else if (lhs.type() == TupleType::POINT && rhs.type() == TupleType::VECTOR)
        {
            return point(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
        }
        else if (lhs.type() == TupleType::VECTOR && rhs.type() == TupleType::VECTOR)
        {
            return vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
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
}

#endif // RAYTRACER_TUPLE_H
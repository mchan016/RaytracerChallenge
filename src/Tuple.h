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
    };

    inline bool operator==(const Tuple& lhs, const Tuple& rhs)
    {
        return doubleEqual(lhs.x(), rhs.x())
            && doubleEqual(lhs.y(), rhs.y()) 
            && doubleEqual(lhs.z(), rhs.z())
            && lhs.type() == rhs.type();
    }

    ////////////////////////////////////
    // FACTORY FUNCTIONS
    ////////////////////////////////////
    std::unique_ptr<Tuple> point(double x, double y, double z);
    std::unique_ptr<Tuple> vector(double x, double y, double z);
}

#endif // RAYTRACER_TUPLE_H
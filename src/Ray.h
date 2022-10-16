#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Tuple.h"

#include <memory>

namespace raytracer
{
    class Ray
    {
    private:
        std::unique_ptr<Tuple> m_origin;
        std::unique_ptr<Tuple> m_direction;

    public:
        Ray();
        Ray(std::unique_ptr<Tuple> origin, std::unique_ptr<Tuple> direction);

        Tuple origin() const;
        Tuple direction() const;

        Tuple position(double t) const;
    };
}

#endif // RAYTRACER_RAY_H
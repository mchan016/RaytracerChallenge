#ifndef RAYTRACER_SHAPES_H
#define RAYTRACER_SHAPES_H

#include <memory>

#include "Tuple.h"

namespace raytracer
{
    class Shape
    {
    private:
        std::unique_ptr<Tuple> m_origin{};

    public:
        virtual ~Shape() = default;
        Tuple origin() const;
        void origin(const Tuple& loc);
    };

    class Sphere : public Shape
    {
    private:
        double m_radius;

    public:
        constexpr static double DEFAULT_RADIUS = 1.0;

        Sphere();
        Sphere(double radius);
        Sphere(const Sphere& other);

        Sphere& operator=(const Sphere& other);
    };

    ////////////////////////////////////
    // FACTORY FUNCTIONS
    ////////////////////////////////////
    Sphere sphere();

} // namespace raytracer


#endif // RAYTRACER_SHAPES_H
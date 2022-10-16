#include "gtest/gtest.h"
#include "Ray.h"
#include "Tuple.h"

using raytracer::Tuple;
using raytracer::Ray;

TEST(RayTest, initRayTest)
{
    auto origin = raytracer::point(1, 2, 3);
    auto direction = raytracer::vector(4, 5, 6);

    Ray ray{std::move(origin), std::move(direction)};

    EXPECT_TRUE(ray.origin() == *raytracer::point(1, 2, 3));
    EXPECT_TRUE(ray.direction() == *raytracer::vector(4, 5, 6));
}

TEST(RayTest, rayPositionTest)
{
    Ray ray{raytracer::point(2, 3, 4), raytracer::vector(1, 0, 0)};

    ASSERT_TRUE(ray.position(0) == *raytracer::point(2, 3, 4));
    EXPECT_TRUE(ray.position(1) == *raytracer::point(3, 3, 4));
    EXPECT_TRUE(ray.position(-1) == *raytracer::point(1, 3, 4));
    EXPECT_TRUE(ray.position(2.5) == *raytracer::point(4.5, 3, 4));
}
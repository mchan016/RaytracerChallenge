#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Tuple.h"
#include "Canvas.h"

#include <stdexcept>


TEST(CanvasTest, initCanvasTest)
{
    raytracer::Canvas c1{10, 20}; // width: 10, height: 20
    ASSERT_EQ(c1.width(), 10);
    ASSERT_EQ(c1.height(), 20);
    
    bool isDefaultColors = true;
    raytracer::Tuple t1{0, 0, 0, raytracer::TupleType::COLOR};
    for (const auto& pixels : c1.canvas())
    {
        for (const auto& pixel : pixels)
        {
            if (!(pixel == t1))
                isDefaultColors = false;
        }
    }
    ASSERT_TRUE(isDefaultColors);
}

TEST(CanvasTest, pixelTest)
{
    raytracer::Canvas c1{10, 20};

    // Test retrieving pixel
    EXPECT_TRUE(c1.pixel(3, 6) == *raytracer::color(0, 0, 0));
    EXPECT_ANY_THROW(c1.pixel(20, 10));
    EXPECT_ANY_THROW(c1.pixel(10, 20));
    EXPECT_NO_THROW(c1.pixel(0, 0));
    EXPECT_NO_THROW(c1.pixel(19, 9));

    // Test setting pixel
    c1.pixel(3, 6, *raytracer::color(1, 0, 0));
    EXPECT_TRUE(c1.pixel(3, 6) == *raytracer::color(1, 0, 0));
    EXPECT_FALSE(c1.pixel(3, 6) == *raytracer::color(0, 1, 1));

    c1.pixel(19, 9, *raytracer::color(0, 0.9, 0.24));
    EXPECT_TRUE(c1.pixel(19, 9) == *raytracer::color(0, 0.9, 0.24));
    EXPECT_FALSE(c1.pixel(19, 9) == *raytracer::color(1, 0, 1));
}
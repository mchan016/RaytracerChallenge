#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Tuple.h"
#include "Canvas.h"

TEST(CanvasTest, initCanvasTest)
{
    raytracer::Canvas c1{10, 20};
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
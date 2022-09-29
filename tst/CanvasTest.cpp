#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Tuple.h"
#include "Canvas.h"

#include <stdexcept>
#include <string>
#include <sstream>

TEST(CanvasTest, initCanvasTest)
{
    raytracer::Canvas canvas{10, 20}; // width: 10, height: 20
    ASSERT_EQ(canvas.width(), 10);
    ASSERT_EQ(canvas.height(), 20);
    
    bool isDefaultColors = true;
    raytracer::Tuple t1{0, 0, 0, raytracer::TupleType::COLOR};
    for (const auto& pixels : canvas.canvas())
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
    EXPECT_NO_THROW(c1.pixel(9, 19));

    // Test setting pixel
    c1.pixel(3, 6, *raytracer::color(1, 0, 0));
    EXPECT_TRUE(c1.pixel(3, 6) == *raytracer::color(1, 0, 0));
    EXPECT_FALSE(c1.pixel(3, 6) == *raytracer::color(0, 1, 1));

    c1.pixel(9, 19, *raytracer::color(0, 0.9, 0.24));
    EXPECT_TRUE(c1.pixel(9, 19) == *raytracer::color(0, 0.9, 0.24));
    EXPECT_FALSE(c1.pixel(9, 19) == *raytracer::color(1, 0, 1));
}

TEST(CanvasTest, canvasToPPMTest)
{
    raytracer::Canvas canvas{5, 3};

    auto c1 = raytracer::color(1.5, 0, 0);
    auto c2 = raytracer::color(0, 0.5, 0);
    auto c3 = raytracer::color(-0.5, 0, 1);

    canvas.pixel(0, 0, *c1);
    canvas.pixel(2, 1, *c2);
    canvas.pixel(4, 2, *c3);

    std::stringstream ppm{canvas.canvasToPPM()};
    std::string line{};

    // Test Header
    std::string header{};
    const int headerLength{3};
    for (int i = 0; i < headerLength; i++)
    {
        getline(ppm, line);
        header += line + '\n';
    }
    EXPECT_EQ(header, "P3\n5 3\n255\n");

    // Test Body
    std::string body{};
    while (getline(ppm, line))
    {
        body += line + '\n';
    }
    std::string answer{
        "255 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 128 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 0\n"
        "0 0 255\n"
    };
    EXPECT_EQ(
        body,
        answer
    );
}

TEST(CanvasTest, ppmNewlineEndTest)
{
    raytracer::Canvas canvas{5, 3};

    EXPECT_EQ(canvas.canvasToPPM().back(), '\n');
}
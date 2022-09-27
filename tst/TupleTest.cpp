#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Tuple.h"

#include <cmath>

TEST(TupleTest, pointTest)
{
    raytracer::Tuple t1{4.3, -4.2, 3.1, raytracer::TupleType::POINT};
    EXPECT_TRUE(raytracer::doubleEqual(t1.x(), 4.3));
    EXPECT_TRUE(raytracer::doubleEqual(t1.y(), -4.2));
    EXPECT_TRUE(raytracer::doubleEqual(t1.z(), 3.1));
    EXPECT_NE(t1.type(), raytracer::TupleType::VECTOR);
    EXPECT_EQ(t1.type(), raytracer::TupleType::POINT);
}

TEST(TupleTest, vectorTest)
{
    raytracer::Tuple t1{4.3, -4.2, 3.1, raytracer::TupleType::VECTOR};
    EXPECT_TRUE(raytracer::doubleEqual(t1.x(), 4.3));
    EXPECT_TRUE(raytracer::doubleEqual(t1.y(), -4.2));
    EXPECT_TRUE(raytracer::doubleEqual(t1.z(), 3.1));
    EXPECT_NE(t1.type(), raytracer::TupleType::POINT);
    EXPECT_EQ(t1.type(), raytracer::TupleType::VECTOR);
}

TEST(TupleTest, colorTest)
{
    raytracer::Tuple t1{-0.5, 0.4, 1.7, raytracer::TupleType::COLOR};
    EXPECT_TRUE(raytracer::doubleEqual(t1.x(), -0.5));
    EXPECT_TRUE(raytracer::doubleEqual(t1.y(), 0.4));
    EXPECT_TRUE(raytracer::doubleEqual(t1.z(), 1.7));
    EXPECT_NE(t1.type(), raytracer::TupleType::POINT);
    EXPECT_NE(t1.type(), raytracer::TupleType::VECTOR);
    EXPECT_EQ(t1.type(), raytracer::TupleType::COLOR);
}

TEST(TupleTest, createPointTest)
{
    std::unique_ptr<raytracer::Tuple> t1 = raytracer::point(4, -4, 3);
    EXPECT_TRUE((*t1 == raytracer::Tuple{4, -4, 3, raytracer::TupleType::POINT}));
}

TEST(TupleTest, createVectorTest)
{
    std::unique_ptr<raytracer::Tuple> t1 = raytracer::vector(4, -4, 3);
    EXPECT_TRUE((*t1 == raytracer::Tuple{4, -4, 3, raytracer::TupleType::VECTOR}));
}

TEST(TupleTest, createColorTest)
{
    std::unique_ptr<raytracer::Tuple> t1 = raytracer::color(4, -4, 3);
    EXPECT_TRUE((*t1 == raytracer::Tuple{4, -4, 3, raytracer::TupleType::COLOR}));
}

TEST(TupleTest, addTupleTest)
{
    raytracer::Tuple t1{3, -2, 5, raytracer::TupleType::POINT};
    raytracer::Tuple t2{-2, 3, 1, raytracer::TupleType::VECTOR};
    raytracer::Tuple t3{0.9, 0.6, 0.75, raytracer::TupleType::COLOR};
    raytracer::Tuple t4{0.7, 0.1, 0.25, raytracer::TupleType::COLOR};

    EXPECT_TRUE((*(t1 + t2) == raytracer::Tuple{1, 1, 6, raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(t2 + t2) == raytracer::Tuple{-4, 6, 2, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t3 + t4) == raytracer::Tuple{1.6, 0.7, 1.0, raytracer::TupleType::COLOR}));
    EXPECT_TRUE(((t1 + t1) == nullptr));
}

TEST(TupleTest, subtractTupleTest)
{
    raytracer::Tuple t1{3, 2, 1, raytracer::TupleType::POINT};
    raytracer::Tuple t2{5, 6, 7, raytracer::TupleType::POINT};
    raytracer::Tuple t3{5, 6, 7, raytracer::TupleType::VECTOR};
    raytracer::Tuple t4{3, 2, 1, raytracer::TupleType::VECTOR};
    raytracer::Tuple t5{0.9, 0.6, 0.75, raytracer::TupleType::COLOR};
    raytracer::Tuple t6{0.7, 0.1, 0.25, raytracer::TupleType::COLOR};

    EXPECT_TRUE((*(t1 - t2) == raytracer::Tuple{-2, -4, -6, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t1 - t3) == raytracer::Tuple{-2, -4, -6, raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(t4 - t3) == raytracer::Tuple{-2, -4, -6, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t5 - t6) == raytracer::Tuple{0.2, 0.5, 0.5, raytracer::TupleType::COLOR}));
    EXPECT_TRUE(((t3 - t2) == nullptr));
}

TEST(TupleTest, negateTupleTest)
{
    raytracer::Tuple t1{5, 6, 7, raytracer::TupleType::POINT};
    raytracer::Tuple t2{5, 6, 7, raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*(-t1) == raytracer::Tuple{-5, -6, -7, raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(-t2) == raytracer::Tuple{-5, -6 ,-7, raytracer::TupleType::VECTOR}));
}

TEST(TupleTest, scalarMultiplicationTest)
{
    raytracer::Tuple t1{1, -2, 3, raytracer::TupleType::VECTOR};
    raytracer::Tuple t2{0.2, 0.3, 0.4, raytracer::TupleType::COLOR};

    EXPECT_TRUE((*(t1 * 3.5) == raytracer::Tuple{3.5, -7, 10.5, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t1 * 0.5) == raytracer::Tuple{0.5, -1, 1.5, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(3.5 * t1) == raytracer::Tuple{3.5, -7, 10.5, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(0.5 * t1) == raytracer::Tuple{0.5, -1, 1.5, raytracer::TupleType::VECTOR}));

    EXPECT_TRUE((*(t2 * 2) == raytracer::Tuple{0.4, 0.6, 0.8, raytracer::TupleType::COLOR}));
    EXPECT_TRUE((*(2 * t2) == raytracer::Tuple{0.4, 0.6, 0.8, raytracer::TupleType::COLOR}));
}

TEST(TupleTest, scalarDivisionTest)
{
    raytracer::Tuple t1{1, -2, 3, raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*(t1 / 2) == raytracer::Tuple{0.5, -1, 1.5, raytracer::TupleType::VECTOR}));
}

TEST(TupleTest, magnitudeTupleTest)
{
    raytracer::Tuple t1{1, 0, 0, raytracer::TupleType::VECTOR};
    raytracer::Tuple t2{0, 1, 0, raytracer::TupleType::VECTOR};
    raytracer::Tuple t3{0, 0, 1, raytracer::TupleType::VECTOR};
    raytracer::Tuple t4{1, 2, 3, raytracer::TupleType::VECTOR};
    raytracer::Tuple t5{-1, -2, -3, raytracer::TupleType::VECTOR};

    EXPECT_TRUE(raytracer::doubleEqual(t1.magnitude(), 1));
    EXPECT_TRUE(raytracer::doubleEqual(t2.magnitude(), 1));
    EXPECT_TRUE(raytracer::doubleEqual(t3.magnitude(), 1));
    EXPECT_TRUE(raytracer::doubleEqual(t4.magnitude(), std::sqrt(14)));
    EXPECT_TRUE(raytracer::doubleEqual(t5.magnitude(), std::sqrt(14)));
}

TEST(TupleTest, normalizeTupleTest)
{
    raytracer::Tuple t1{4, 0, 0, raytracer::TupleType::VECTOR};
    raytracer::Tuple t2{1, 2, 3, raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*t1.normalize() == raytracer::Tuple{1, 0, 0, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*t2.normalize() == raytracer::Tuple{0.26726, 0.53452, 0.80178, raytracer::TupleType::VECTOR}));
    EXPECT_TRUE(raytracer::doubleEqual(t2.normalize()->magnitude(), 1));
}

TEST(TupleTest, dotProductTest)
{
    raytracer::Tuple t1{1, 2, 3, raytracer::TupleType::VECTOR};
    raytracer::Tuple t2{2, 3, 4, raytracer::TupleType::VECTOR};

    EXPECT_TRUE(raytracer::doubleEqual(raytracer::dot(t1, t2), 20));
}

TEST(TupleTest, crossProductTest)
{
    raytracer::Tuple t1{1, 2, 3, raytracer::TupleType::VECTOR};
    raytracer::Tuple t2{2, 3, 4, raytracer::TupleType::VECTOR};

    EXPECT_TRUE(((*raytracer::cross(t1, t2) == raytracer::Tuple{-1, 2, -1, raytracer::TupleType::VECTOR})));
    EXPECT_TRUE(((*raytracer::cross(t2, t1) == raytracer::Tuple{1, -2, 1, raytracer::TupleType::VECTOR})));
}
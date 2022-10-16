#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Tuple.h"

#include <cmath>

using raytracer::Tuple;
using raytracer::TupleType;
using raytracer::doubleEqual;

TEST(TupleTest, pointTest)
{
    Tuple t1{4.3, -4.2, 3.1, TupleType::POINT};
    EXPECT_TRUE(doubleEqual(t1.x(), 4.3));
    EXPECT_TRUE(doubleEqual(t1.y(), -4.2));
    EXPECT_TRUE(doubleEqual(t1.z(), 3.1));
    EXPECT_NE(t1.type(), TupleType::VECTOR);
    EXPECT_EQ(t1.type(), TupleType::POINT);
}

TEST(TupleTest, vectorTest)
{
    Tuple t1{4.3, -4.2, 3.1, TupleType::VECTOR};
    EXPECT_TRUE(doubleEqual(t1.x(), 4.3));
    EXPECT_TRUE(doubleEqual(t1.y(), -4.2));
    EXPECT_TRUE(doubleEqual(t1.z(), 3.1));
    EXPECT_NE(t1.type(), TupleType::POINT);
    EXPECT_EQ(t1.type(), TupleType::VECTOR);
}

TEST(TupleTest, colorTest)
{
    Tuple t1{-0.5, 0.4, 1.7, TupleType::COLOR};
    EXPECT_TRUE(doubleEqual(t1.x(), -0.5));
    EXPECT_TRUE(doubleEqual(t1.y(), 0.4));
    EXPECT_TRUE(doubleEqual(t1.z(), 1.7));
    EXPECT_NE(t1.type(), TupleType::POINT);
    EXPECT_NE(t1.type(), TupleType::VECTOR);
    EXPECT_EQ(t1.type(), TupleType::COLOR);
}

TEST(TupleTest, createPointTest)
{
    Tuple t1 = raytracer::point(4, -4, 3);
    EXPECT_TRUE((t1 == Tuple{4, -4, 3, TupleType::POINT}));
}

TEST(TupleTest, createVectorTest)
{
    Tuple t1 = raytracer::vector(4, -4, 3);
    EXPECT_TRUE((t1 == Tuple{4, -4, 3, TupleType::VECTOR}));
}

TEST(TupleTest, createColorTest)
{
    Tuple t1 = raytracer::color(4, -4, 3);
    EXPECT_TRUE((t1 == Tuple{4, -4, 3, TupleType::COLOR}));
}

TEST(TupleTest, addTupleTest)
{
    Tuple t1{3, -2, 5, TupleType::POINT};
    Tuple t2{-2, 3, 1, TupleType::VECTOR};
    Tuple t3{0.9, 0.6, 0.75, TupleType::COLOR};
    Tuple t4{0.7, 0.1, 0.25, TupleType::COLOR};

    EXPECT_TRUE(((t1 + t2) == Tuple{1, 1, 6, TupleType::POINT}));
    EXPECT_TRUE(((t2 + t2) == Tuple{-4, 6, 2, TupleType::VECTOR}));
    EXPECT_TRUE(((t3 + t4) == Tuple{1.6, 0.7, 1.0, TupleType::COLOR}));
    EXPECT_TRUE(((t1 + t1) == Tuple{}));
}

TEST(TupleTest, subtractTupleTest)
{
    Tuple t1{3, 2, 1, TupleType::POINT};
    Tuple t2{5, 6, 7, TupleType::POINT};
    Tuple t3{5, 6, 7, TupleType::VECTOR};
    Tuple t4{3, 2, 1, TupleType::VECTOR};
    Tuple t5{0.9, 0.6, 0.75, TupleType::COLOR};
    Tuple t6{0.7, 0.1, 0.25, TupleType::COLOR};

    EXPECT_TRUE(((t1 - t2) == Tuple{-2, -4, -6, TupleType::VECTOR}));
    EXPECT_TRUE(((t1 - t3) == Tuple{-2, -4, -6, TupleType::POINT}));
    EXPECT_TRUE(((t4 - t3) == Tuple{-2, -4, -6, TupleType::VECTOR}));
    EXPECT_TRUE(((t5 - t6) == Tuple{0.2, 0.5, 0.5, TupleType::COLOR}));
    EXPECT_TRUE(((t3 - t2) == Tuple{}));
}

TEST(TupleTest, negateTupleTest)
{
    Tuple t1{5, 6, 7, TupleType::POINT};
    Tuple t2{5, 6, 7, TupleType::VECTOR};

    EXPECT_TRUE((-t1 == Tuple{-5, -6, -7, TupleType::POINT}));
    EXPECT_TRUE((-t2 == Tuple{-5, -6 ,-7, TupleType::VECTOR}));
}

TEST(TupleTest, scalarMultiplicationTest)
{
    Tuple t1{1, -2, 3, TupleType::VECTOR};
    Tuple t2{0.2, 0.3, 0.4, TupleType::COLOR};

    EXPECT_TRUE(((t1 * 3.5) == Tuple{3.5, -7, 10.5, TupleType::VECTOR}));
    EXPECT_TRUE(((t1 * 0.5) == Tuple{0.5, -1, 1.5, TupleType::VECTOR}));
    EXPECT_TRUE(((3.5 * t1) == Tuple{3.5, -7, 10.5, TupleType::VECTOR}));
    EXPECT_TRUE(((0.5 * t1) == Tuple{0.5, -1, 1.5, TupleType::VECTOR}));

    EXPECT_TRUE(((t2 * 2) == Tuple{0.4, 0.6, 0.8, TupleType::COLOR}));
    EXPECT_TRUE(((2 * t2) == Tuple{0.4, 0.6, 0.8, TupleType::COLOR}));
}

TEST(TupleTest, tupleMultiplicationTest)
{
    Tuple t1{1, 0.2, 0.4, TupleType::COLOR};
    Tuple t2{0.9, 1, 0.1, TupleType::COLOR};

    EXPECT_TRUE(((t1 * t2) == Tuple{0.9, 0.2, 0.04, TupleType::COLOR}));
}

TEST(TupleTest, scalarDivisionTest)
{
    Tuple t1{1, -2, 3, TupleType::VECTOR};

    EXPECT_TRUE(((t1 / 2) == Tuple{0.5, -1, 1.5, TupleType::VECTOR}));
}

TEST(TupleTest, magnitudeTupleTest)
{
    Tuple t1{1, 0, 0, TupleType::VECTOR};
    Tuple t2{0, 1, 0, TupleType::VECTOR};
    Tuple t3{0, 0, 1, TupleType::VECTOR};
    Tuple t4{1, 2, 3, TupleType::VECTOR};
    Tuple t5{-1, -2, -3, TupleType::VECTOR};

    EXPECT_TRUE(doubleEqual(t1.magnitude(), 1));
    EXPECT_TRUE(doubleEqual(t2.magnitude(), 1));
    EXPECT_TRUE(doubleEqual(t3.magnitude(), 1));
    EXPECT_TRUE(doubleEqual(t4.magnitude(), std::sqrt(14)));
    EXPECT_TRUE(doubleEqual(t5.magnitude(), std::sqrt(14)));
}

TEST(TupleTest, normalizeTupleTest)
{
    Tuple t1{4, 0, 0, TupleType::VECTOR};
    Tuple t2{1, 2, 3, TupleType::VECTOR};

    EXPECT_TRUE((t1.normalize() == Tuple{1, 0, 0, TupleType::VECTOR}));
    EXPECT_TRUE((t2.normalize() == Tuple{0.26726, 0.53452, 0.80178, TupleType::VECTOR}));
    EXPECT_TRUE(doubleEqual(t2.normalize().magnitude(), 1));
}

TEST(TupleTest, dotProductTest)
{
    Tuple t1{1, 2, 3, TupleType::VECTOR};
    Tuple t2{2, 3, 4, TupleType::VECTOR};

    EXPECT_TRUE(doubleEqual(raytracer::dot(t1, t2), 20));
}

TEST(TupleTest, crossProductTest)
{
    Tuple t1{1, 2, 3, TupleType::VECTOR};
    Tuple t2{2, 3, 4, TupleType::VECTOR};

    EXPECT_TRUE(((raytracer::cross(t1, t2) == Tuple{-1, 2, -1, TupleType::VECTOR})));
    EXPECT_TRUE(((raytracer::cross(t2, t1) == Tuple{1, -2, 1, TupleType::VECTOR})));
}
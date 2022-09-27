#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Tuple.h"

#include <cmath>

TEST(TupleTest, pointTest)
{
    Raytracer::Tuple t1{4.3, -4.2, 3.1, Raytracer::TupleType::POINT};
    EXPECT_TRUE(Raytracer::doubleEqual(t1.x(), 4.3));
    EXPECT_TRUE(Raytracer::doubleEqual(t1.y(), -4.2));
    EXPECT_TRUE(Raytracer::doubleEqual(t1.z(), 3.1));
    EXPECT_NE(t1.type(), Raytracer::TupleType::VECTOR);
    EXPECT_EQ(t1.type(), Raytracer::TupleType::POINT);
}

TEST(TupleTest, vectorTest)
{
    Raytracer::Tuple t1{4.3, -4.2, 3.1, Raytracer::TupleType::VECTOR};
    EXPECT_TRUE(Raytracer::doubleEqual(t1.x(), 4.3));
    EXPECT_TRUE(Raytracer::doubleEqual(t1.y(), -4.2));
    EXPECT_TRUE(Raytracer::doubleEqual(t1.z(), 3.1));
    EXPECT_NE(t1.type(), Raytracer::TupleType::POINT);
    EXPECT_EQ(t1.type(), Raytracer::TupleType::VECTOR);
}

TEST(TupleTest, colorTest)
{
    Raytracer::Tuple t1{-0.5, 0.4, 1.7, Raytracer::TupleType::COLOR};
    EXPECT_TRUE(Raytracer::doubleEqual(t1.x(), -0.5));
    EXPECT_TRUE(Raytracer::doubleEqual(t1.y(), 0.4));
    EXPECT_TRUE(Raytracer::doubleEqual(t1.z(), 1.7));
    EXPECT_NE(t1.type(), Raytracer::TupleType::POINT);
    EXPECT_NE(t1.type(), Raytracer::TupleType::VECTOR);
    EXPECT_EQ(t1.type(), Raytracer::TupleType::COLOR);
}

TEST(TupleTest, createPointTest)
{
    std::unique_ptr<Raytracer::Tuple> t1 = Raytracer::point(4, -4, 3);
    EXPECT_TRUE((*t1 == Raytracer::Tuple{4, -4, 3, Raytracer::TupleType::POINT}));
}

TEST(TupleTest, createVectorTest)
{
    std::unique_ptr<Raytracer::Tuple> t1 = Raytracer::vector(4, -4, 3);
    EXPECT_TRUE((*t1 == Raytracer::Tuple{4, -4, 3, Raytracer::TupleType::VECTOR}));
}

TEST(TupleTest, createColorTest)
{
    std::unique_ptr<Raytracer::Tuple> t1 = Raytracer::color(4, -4, 3);
    EXPECT_TRUE((*t1 == Raytracer::Tuple{4, -4, 3, Raytracer::TupleType::COLOR}));
}

TEST(TupleTest, addTupleTest)
{
    Raytracer::Tuple t1{3, -2, 5, Raytracer::TupleType::POINT};
    Raytracer::Tuple t2{-2, 3, 1, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t3{0.9, 0.6, 0.75, Raytracer::TupleType::COLOR};
    Raytracer::Tuple t4{0.7, 0.1, 0.25, Raytracer::TupleType::COLOR};

    EXPECT_TRUE((*(t1 + t2) == Raytracer::Tuple{1, 1, 6, Raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(t2 + t2) == Raytracer::Tuple{-4, 6, 2, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t3 + t4) == Raytracer::Tuple{1.6, 0.7, 1.0, Raytracer::TupleType::COLOR}));
    EXPECT_TRUE(((t1 + t1) == nullptr));
}

TEST(TupleTest, subtractTupleTest)
{
    Raytracer::Tuple t1{3, 2, 1, Raytracer::TupleType::POINT};
    Raytracer::Tuple t2{5, 6, 7, Raytracer::TupleType::POINT};
    Raytracer::Tuple t3{5, 6, 7, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t4{3, 2, 1, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t5{0.9, 0.6, 0.75, Raytracer::TupleType::COLOR};
    Raytracer::Tuple t6{0.7, 0.1, 0.25, Raytracer::TupleType::COLOR};

    EXPECT_TRUE((*(t1 - t2) == Raytracer::Tuple{-2, -4, -6, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t1 - t3) == Raytracer::Tuple{-2, -4, -6, Raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(t4 - t3) == Raytracer::Tuple{-2, -4, -6, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t5 - t6) == Raytracer::Tuple{0.2, 0.5, 0.5, Raytracer::TupleType::COLOR}));
    EXPECT_TRUE(((t3 - t2) == nullptr));
}

TEST(TupleTest, negateTupleTest)
{
    Raytracer::Tuple t1{5, 6, 7, Raytracer::TupleType::POINT};
    Raytracer::Tuple t2{5, 6, 7, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*(-t1) == Raytracer::Tuple{-5, -6, -7, Raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(-t2) == Raytracer::Tuple{-5, -6 ,-7, Raytracer::TupleType::VECTOR}));
}

TEST(TupleTest, scalarMultiplicationTest)
{
    Raytracer::Tuple t1{1, -2, 3, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t2{0.2, 0.3, 0.4, Raytracer::TupleType::COLOR};

    EXPECT_TRUE((*(t1 * 3.5) == Raytracer::Tuple{3.5, -7, 10.5, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t1 * 0.5) == Raytracer::Tuple{0.5, -1, 1.5, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(3.5 * t1) == Raytracer::Tuple{3.5, -7, 10.5, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(0.5 * t1) == Raytracer::Tuple{0.5, -1, 1.5, Raytracer::TupleType::VECTOR}));

    EXPECT_TRUE((*(t2 * 2) == Raytracer::Tuple{0.4, 0.6, 0.8, Raytracer::TupleType::COLOR}));
    EXPECT_TRUE((*(2 * t2) == Raytracer::Tuple{0.4, 0.6, 0.8, Raytracer::TupleType::COLOR}));
}

TEST(TupleTest, scalarDivisionTest)
{
    Raytracer::Tuple t1{1, -2, 3, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*(t1 / 2) == Raytracer::Tuple{0.5, -1, 1.5, Raytracer::TupleType::VECTOR}));
}

TEST(TupleTest, magnitudeTupleTest)
{
    Raytracer::Tuple t1{1, 0, 0, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t2{0, 1, 0, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t3{0, 0, 1, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t4{1, 2, 3, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t5{-1, -2, -3, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE(Raytracer::doubleEqual(t1.magnitude(), 1));
    EXPECT_TRUE(Raytracer::doubleEqual(t2.magnitude(), 1));
    EXPECT_TRUE(Raytracer::doubleEqual(t3.magnitude(), 1));
    EXPECT_TRUE(Raytracer::doubleEqual(t4.magnitude(), std::sqrt(14)));
    EXPECT_TRUE(Raytracer::doubleEqual(t5.magnitude(), std::sqrt(14)));
}

TEST(TupleTest, normalizeTupleTest)
{
    Raytracer::Tuple t1{4, 0, 0, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t2{1, 2, 3, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*t1.normalize() == Raytracer::Tuple{1, 0, 0, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*t2.normalize() == Raytracer::Tuple{0.26726, 0.53452, 0.80178, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE(Raytracer::doubleEqual(t2.normalize()->magnitude(), 1));
}

TEST(TupleTest, dotProductTest)
{
    Raytracer::Tuple t1{1, 2, 3, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t2{2, 3, 4, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE(Raytracer::doubleEqual(Raytracer::dot(t1, t2), 20));
}

TEST(TupleTest, crossProductTest)
{
    Raytracer::Tuple t1{1, 2, 3, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t2{2, 3, 4, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE(((*Raytracer::cross(t1, t2) == Raytracer::Tuple{-1, 2, -1, Raytracer::TupleType::VECTOR})));
    EXPECT_TRUE(((*Raytracer::cross(t2, t1) == Raytracer::Tuple{1, -2, 1, Raytracer::TupleType::VECTOR})));
}
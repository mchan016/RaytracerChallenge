#include "gtest/gtest.h"
#include "RaytracerUtils.h"
#include "Tuple.h"

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

TEST(TupleTest, addTupleTest)
{
    Raytracer::Tuple t1{3, -2, 5, Raytracer::TupleType::POINT};
    Raytracer::Tuple t2{-2, 3, 1, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*(t1 + t2) == Raytracer::Tuple{1, 1, 6, Raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(t2 + t2) == Raytracer::Tuple{-4, 6, 2, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE(((t1 + t1) == nullptr));
}

TEST(TupleTest, subtractTupleTest)
{
    Raytracer::Tuple t1{3, 2, 1, Raytracer::TupleType::POINT};
    Raytracer::Tuple t2{5, 6, 7, Raytracer::TupleType::POINT};
    Raytracer::Tuple t3{5, 6, 7, Raytracer::TupleType::VECTOR};
    Raytracer::Tuple t4{3, 2, 1, Raytracer::TupleType::VECTOR};

    EXPECT_TRUE((*(t1 - t2) == Raytracer::Tuple{-2, -4, -6, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE((*(t1 - t3) == Raytracer::Tuple{-2, -4, -6, Raytracer::TupleType::POINT}));
    EXPECT_TRUE((*(t4 - t3) == Raytracer::Tuple{-2, -4, -6, Raytracer::TupleType::VECTOR}));
    EXPECT_TRUE(((t3 - t2) == nullptr));
}
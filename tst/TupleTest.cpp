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
    Raytracer::Tuple* t1 = Raytracer::point(4, -4, 3);
    EXPECT_TRUE((*t1 == Raytracer::Tuple{4, -4, 3, Raytracer::TupleType::POINT}));
}

TEST(TupleTest, createVectorTest)
{
    Raytracer::Tuple* t1 = Raytracer::vector(4, -4, 3);
    EXPECT_TRUE((*t1 == Raytracer::Tuple{4, -4, 3, Raytracer::TupleType::VECTOR}));
}
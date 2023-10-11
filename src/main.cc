#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "inc/Fraction.hh"

// Constructors
TEST(EmptyConstructor, _) {
    Fraction fraction;

    ASSERT_EQ(fraction.number(), 0);
    ASSERT_EQ(fraction.numerator(), 0);
    ASSERT_EQ(fraction.denominator(), 1);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(ManualConstructor, DenominatorEquals0) {
    ASSERT_DEATH({ Fraction fraction(3, 11, 0); }, "Denominator may not be 0!");
}

TEST(ManualConstructor, NumeratorEquals0) {
    Fraction fraction(1, 0, 15, false);

    ASSERT_EQ(fraction.number(), 1);
    ASSERT_EQ(fraction.numerator(), 0);
    ASSERT_EQ(fraction.denominator(), 1);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(ManualConstructor, FractionReduce) {
    Fraction fraction(3, 11, 5, true);

    ASSERT_EQ(fraction.number(), 5);
    ASSERT_EQ(fraction.numerator(), 1);
    ASSERT_EQ(fraction.denominator(), 5);
    ASSERT_EQ(fraction.sign(), true);
}

TEST(FromFractionConstructor, IsEqual) {
    Fraction fraction0(3, 11, 5);
    Fraction fraction(fraction0);

    ASSERT_EQ(fraction.number(), 5);
    ASSERT_EQ(fraction.numerator(), 1);
    ASSERT_EQ(fraction.denominator(), 5);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(FromStringConstructor, Full) {
    Fraction fraction("-3 11/5");

    ASSERT_EQ(fraction.number(), 5);
    ASSERT_EQ(fraction.numerator(), 1);
    ASSERT_EQ(fraction.denominator(), 5);
    ASSERT_EQ(fraction.sign(), true);
}

TEST(FromStringConstructor, OnlyFraction) {
    Fraction fraction("-10/15");

    ASSERT_EQ(fraction.number(), 0);
    ASSERT_EQ(fraction.numerator(), 2);
    ASSERT_EQ(fraction.denominator(), 3);
    ASSERT_EQ(fraction.sign(), true);
}

TEST(FromStringConstructor, OnlyNumber) {
    Fraction fraction("+10");

    ASSERT_EQ(fraction.number(), 10);
    ASSERT_EQ(fraction.numerator(), 0);
    ASSERT_EQ(fraction.denominator(), 1);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(FromStringConstructor, OnlySign) {
    ASSERT_DEATH({ Fraction fraction("+"); }, "Does not match pattern");
}

TEST(FromStringConstructor, Empty) {
    ASSERT_DEATH({ Fraction fraction(""); }, "Does not match pattern");
}

int
main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

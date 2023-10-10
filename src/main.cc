#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "inc/Fraction.hh"

// Constructors
TEST(ManualConstructor, DenominatorEquals0) {
    ASSERT_DEATH({ Fraction fraction(3, 11, 0); }, "Denominator may not be 0!");
}

TEST(ManualConstructor, NumeratorEquals0) {
    Fraction fraction(1, 0, 15, false);

    ASSERT_EQ(fraction.get_number(), 1);
    ASSERT_EQ(fraction.get_numerator(), 0);
    ASSERT_EQ(fraction.get_denominator(), 1);
    ASSERT_EQ(fraction.get_sign(), false);
}

TEST(ManualConstructor, FractionReduce) {
    Fraction fraction(3, 11, 5, true);

    ASSERT_EQ(fraction.get_number(), 5);
    ASSERT_EQ(fraction.get_numerator(), 1);
    ASSERT_EQ(fraction.get_denominator(), 5);
    ASSERT_EQ(fraction.get_sign(), true);
}

TEST(FromFractionConstructor, IsEqual) {
    Fraction fraction0(3, 11, 5);
    Fraction fraction(fraction0);

    ASSERT_EQ(fraction.get_number(), 5);
    ASSERT_EQ(fraction.get_numerator(), 1);
    ASSERT_EQ(fraction.get_denominator(), 5);
    ASSERT_EQ(fraction.get_sign(), false);
}

TEST(FromStringConstructor, Full) {
    Fraction fraction("-3 11/5");

    ASSERT_EQ(fraction.get_number(), 5);
    ASSERT_EQ(fraction.get_numerator(), 1);
    ASSERT_EQ(fraction.get_denominator(), 5);
    ASSERT_EQ(fraction.get_sign(), true);
}

TEST(FromStringConstructor, OnlyFraction) {
    Fraction fraction("-10/15");

    ASSERT_EQ(fraction.get_number(), 0);
    ASSERT_EQ(fraction.get_numerator(), 2);
    ASSERT_EQ(fraction.get_denominator(), 3);
    ASSERT_EQ(fraction.get_sign(), true);
}

TEST(FromStringConstructor, OnlyNumber) {
    Fraction fraction("+10");

    ASSERT_EQ(fraction.get_number(), 10);
    ASSERT_EQ(fraction.get_numerator(), 0);
    ASSERT_EQ(fraction.get_denominator(), 1);
    ASSERT_EQ(fraction.get_sign(), false);
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

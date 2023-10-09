#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include "inc/Fraction.hh"

TEST(ManualConstructor, DenominatorEquals0) {
    ASSERT_DEATH({ Fraction fraction(3, 11, 0); }, "Denominator may not be 0!");
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

int
main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

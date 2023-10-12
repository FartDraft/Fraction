#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "inc/Fraction.hh"

using namespace fraction;

// Constructors
TEST(EmptyConstructor, _) {
    Fraction fraction;

    ASSERT_EQ(fraction.number(), 0);
    ASSERT_EQ(fraction.numerator(), 0);
    ASSERT_EQ(fraction.denominator(), 1);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(FromSelfConstructor, _) {
    Fraction fraction0(3, 11, 5);
    Fraction fraction(fraction0);

    ASSERT_EQ(fraction.number(), 5);
    ASSERT_EQ(fraction.numerator(), 1);
    ASSERT_EQ(fraction.denominator(), 5);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(ManualConstructor, DenominatorEquals0) {
    ASSERT_DEATH({ Fraction fraction(3, 11, 0); }, "denominator may not be 0!");
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

TEST(FromDoubleConstructor, Pi) {
    double d = 3.14159;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
}

TEST(FromDoubleConstructor, E) {
    double d = -2.71828;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
}

TEST(FromDoubleConstructor, Int) {
    double d = 5;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
}

TEST(FromDoubleConstructor, Zero) {
    double d = 0;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
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

TEST(FromStringConstructor, Double) {
    Fraction a("3.14");
    Fraction b(3.14);

    ASSERT_EQ(cmp(a, b), 0);
}

// Methods
TEST(Cmp, Equal0) {
    Fraction a;
    Fraction b;

    ASSERT_EQ(cmp(a, b), 0);
}

TEST(Cmp, EqualFractionReduce) {
    Fraction a(3, 11, 5);
    Fraction b(5, 1, 5);

    ASSERT_EQ(cmp(a, b), 0);
}

TEST(Cmp, Less) {
    Fraction a(2.71);
    Fraction b(3.14);

    ASSERT_EQ(cmp(a, b), -1);
}

TEST(Cmp, Greater) {
    Fraction b("2.71");
    Fraction a("3.14");

    ASSERT_EQ(cmp(a, b), 1);
}

TEST(Cmp, Minus) {
    Fraction a("-5 119/130");
    Fraction b("0 1/2");

    ASSERT_EQ(cmp(a, b), -1);
}

int
main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

#include "_utility.hh"

// Empty
TEST(ConstructorEmpty, _) {
    Fraction fraction;

    ASSERT_EQ(fraction.number(), 0);
    ASSERT_EQ(fraction.numerator(), 0);
    ASSERT_EQ(fraction.denominator(), 1);
    ASSERT_EQ(fraction.sign(), false);
}

// Self
TEST(ConstructorSelf, _) {
    Fraction fraction0(3, 11, 5);
    Fraction fraction(fraction0);

    ASSERT_EQ(fraction.number(), 5);
    ASSERT_EQ(fraction.numerator(), 1);
    ASSERT_EQ(fraction.denominator(), 5);
    ASSERT_EQ(fraction.sign(), false);
}

// Manual
TEST(ConstructorManual, DenominatorEquals0) {
    ASSERT_DEATH({ Fraction fraction(3, 11, 0); }, "denominator may not be 0!");
}

TEST(ConstructorManual, NumeratorEquals0) {
    Fraction fraction(1, 0, 15, false);

    ASSERT_EQ(fraction.number(), 1);
    ASSERT_EQ(fraction.numerator(), 0);
    ASSERT_EQ(fraction.denominator(), 1);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(ConstructorManual, FractionReduce) {
    Fraction fraction(3, 11, 5, true);

    ASSERT_EQ(fraction.number(), 5);
    ASSERT_EQ(fraction.numerator(), 1);
    ASSERT_EQ(fraction.denominator(), 5);
    ASSERT_EQ(fraction.sign(), true);
}

// Double
TEST(ConstructorDouble, Pi) {
    double d = 3.14159;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
}

TEST(ConstructorDouble, E) {
    double d = -2.71828;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
}

TEST(ConstructorDouble, Integer) {
    double d = 5;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
}

TEST(ConstructorDouble, Zero) {
    double d = 0;
    Fraction fraction(d);

    ASSERT_EQ(d, (fraction.sign() ? -1.0 : 1.0)
                     * (fraction.number() + (static_cast<double>(fraction.numerator()) / fraction.denominator())));
}

// String
TEST(ConstructorString, Full) {
    Fraction fraction("-3 11/5");

    ASSERT_EQ(fraction.number(), 5);
    ASSERT_EQ(fraction.numerator(), 1);
    ASSERT_EQ(fraction.denominator(), 5);
    ASSERT_EQ(fraction.sign(), true);
}

TEST(ConstructorString, OnlyFraction) {
    Fraction fraction("-10/15");

    ASSERT_EQ(fraction.number(), 0);
    ASSERT_EQ(fraction.numerator(), 2);
    ASSERT_EQ(fraction.denominator(), 3);
    ASSERT_EQ(fraction.sign(), true);
}

TEST(ConstructorString, OnlyNumber) {
    Fraction fraction("+10");

    ASSERT_EQ(fraction.number(), 10);
    ASSERT_EQ(fraction.numerator(), 0);
    ASSERT_EQ(fraction.denominator(), 1);
    ASSERT_EQ(fraction.sign(), false);
}

TEST(ConstructorString, OnlySign) {
    ASSERT_DEATH({ Fraction fraction("+"); }, "Does not match pattern");
}

TEST(ConstructorString, Empty) {
    ASSERT_DEATH({ Fraction fraction(""); }, "Does not match pattern");
}

TEST(ConstructorString, Double) {
    Fraction a("+3.14");
    Fraction b(3.14);

    ASSERT_EQ(cmp(a, b), 0);
}
